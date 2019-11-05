#include "src/Network/v2x_network.h"

#include <Arduino.h>
#include <STM32FreeRTOS.h>

TinyGsm modem(NetSerial);
TinyGsmClient client(modem);
PubSubClient mqtt(client);

long lastReconnectAttempt = 0;

const char* apn = "www.inwi.ma";
const char* gprsUser = "";
const char* gprsPass = "";
const char* broker = "41.140.242.182";
int port = 1338;
const char* topic = "eXPTracker";

void V2X_NETWORK::setup()
{
  pinMode(PB3, OUTPUT);

  apn = "www.inwi.ma";
  gprsUser = "";
  gprsPass = "";
  broker = "41.140.242.182";
  port = 1338;
  topic = "eXPTracker";

  init_Modem();
}

void V2X_NETWORK::loop()
{
  if (!mqtt.connected()) 
  {
    DebugSerial.println("=== NOT CONNECTED ===");
    unsigned long t = millis();
    if (t - lastReconnectAttempt > 5000) 
    {
      lastReconnectAttempt = t;
      if (mqttConnect()) {
        lastReconnectAttempt = 0;
      }
    }
    vTaskDelay( 100 / portTICK_PERIOD_MS );
  }
  mqtt.loop();
}

void init_Modem()
{
  DebugSerial.println("MQTT Task Started !");

  DebugSerial.println("Initializing modem...");
  modem.restart();
  // modem.init();

  String modemInfo = modem.getModemInfo();
  DebugSerial.print("Modem Info: ");
  DebugSerial.println(modemInfo);

  modem.gprsConnect(apn, gprsUser, gprsPass);
  DebugSerial.print("Waiting for network...");
  if (!modem.waitForNetwork()) {
    DebugSerial.println(" fail");
    vTaskDelay(10000 / portTICK_PERIOD_MS );
  }
  DebugSerial.println(" success");

  if (modem.isNetworkConnected()) {
    DebugSerial.println("Network connected");
  }

  DebugSerial.print(F("Connecting to "));
    DebugSerial.print(apn);
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
      DebugSerial.println(" fail");
      vTaskDelay(10000 / portTICK_PERIOD_MS );
    }
    DebugSerial.println(" success");

  if (modem.isGprsConnected()) {
    DebugSerial.println("GPRS connected");
  }

  mqtt.setServer(broker, port);
  mqtt.setCallback(MessageHandler);
}

void MessageHandler(char* topic, byte* payload, unsigned int len) 
{
  DebugSerial.print("Message arrived [");
  DebugSerial.print(topic);
  DebugSerial.print("]: ");
  DebugSerial.write(payload, len);
  DebugSerial.println();

  // Handle Incomming messages : TODO switch case
}

boolean mqttConnect() 
{
  DebugSerial.print("Connecting to ");
  DebugSerial.print(broker);

  // Connect to MQTT Broker
  //boolean status = mqtt.connect("exp101", "exp101", "6482");
  boolean status = mqtt.connect("exp101");

  if (status == false) {
    DebugSerial.println(" fail");
    return false;
  }
  DebugSerial.println(" success");
  //mqtt.publish(pubTopic, "exp101 started");
  mqtt.subscribe(topic);
  return mqtt.connected();
}

void V2X_NETWORK::main(void* p){
  V2X_NETWORK::setup();

  for(;;)
  {
    V2X_NETWORK::loop();

    vTaskDelay(1);
  }
}