#include "src/Network/v2x_network.h"

TinyGsm modem(NetSerial);
TinyGsmClient client(modem);
PubSubClient mqtt(client);

SIM_CONFIG simconfig;

long lastReconnectAttempt = 0;
long lastTransmition = 0;



char* apn = "www.inwi.ma";
char* gprsUser = "";
char* gprsPass = "";
char* broker = "41.140.242.182";
int port = 1338;
char* DeviceID = "expV010_0001";
char* topic = "exp/v010/data";
char* cmdTopic = "expV010_0001/cmd";
String imei = "";

void V2X_NETWORK::setup(SIM_CONFIG* conf)
{
  pinMode(PB3, OUTPUT);
  simconfig = *conf;

  Serial.println("Configuration Loaded :");
  Serial.print("APN : ");
  Serial.print(simconfig.apn);
  Serial.println("");
  Serial.print("USER : ");
  Serial.print(simconfig.gprsUser);
  Serial.println("");
  Serial.print("PASS : ");
  Serial.print(simconfig.gprsPass);
  Serial.println("");
  Serial.print("SERVER : ");
  Serial.print(simconfig.broker);
  Serial.println("");
  Serial.print("PORT : ");
  Serial.print(simconfig.port);
  Serial.println("");
  Serial.print("INTERVAL : ");
  Serial.print(simconfig.interval);
  Serial.println("");

  apn = "www.inwi.ma";
  gprsUser = "";
  gprsPass = "";
  broker = "41.140.242.182";
  port = 1338;
  topic = "exp/v010/data";

  init_Modem();
  modem.enableGPS();
}

void V2X_NETWORK::loop()
{
  unsigned long time = millis();
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
    vTaskDelay( 10 / portTICK_PERIOD_MS );
  }

  if(time - lastTransmition > simconfig.interval)
  {
    String gpsData = FORMATER::GPS_TO_JSON(&modem, imei);
    byte buffer[2048];
    gpsData.getBytes(buffer,gpsData.length()+1);
    for (int i = 0; i <= gpsData.length(); i++)
    {
      Serial.write(buffer[i]);
    }
    Serial.println(" ");
    
    if(mqtt.beginPublish(topic,gpsData.length()+1,false) == 1)
    {
      mqtt.write(buffer,gpsData.length()+1);
      if(mqtt.endPublish()==1)
      {
        DebugSerial.println("SEND OK");
        lastTransmition = time;
      }
      else
      {
        DebugSerial.println("SEND FAIL");
      }
    }
    
    
    /*
    char buffer[1024];
    gpsData.toCharArray(buffer, 1023);
    if(mqtt.publish(topic, buffer))
    {
      DebugSerial.println("SEND OK");
      lastTransmition = time;
    }
    else
    {
      DebugSerial.println("SEND FAIL");
    }
    */
  }

  mqtt.loop();
}

void init_Modem()
{
  DebugSerial.println("MQTT Task Started !");

  DebugSerial.println("Initializing modem...");
  //modem.restart();
  modem.init();

  String modemInfo = modem.getModemInfo();
  DebugSerial.print("Modem Info: ");
  DebugSerial.println(modemInfo);

  imei = modem.getIMEI();

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

  mqtt.setServer(simconfig.broker, simconfig.port);
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
  boolean status = mqtt.connect(DeviceID);

  if (status == false) {
    DebugSerial.println(" fail");
    return false;
  }
  DebugSerial.println(" success");
  mqtt.publish("etrack", "exp20 connected");
  mqtt.subscribe(cmdTopic);
  mqtt.subscribe("EXP/V2X/AUXIN");
  return mqtt.connected();
}

void V2X_NETWORK::main(void* p){

  DebugSerial.println("NET Task Started");
  V2X_NETWORK::setup((SIM_CONFIG*)p);

  for(;;)
  {
    V2X_NETWORK::loop();

    vTaskDelay(1);
  }
}