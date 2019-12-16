#include "v2x_controller.h"

//STATE VARIABLES
extern bool PC_CONNECTION = false;
extern bool BLINK_STATUS = false;
extern bool GPS_STATUS = false;
extern bool NET_STATUS = false;
extern bool IO_STATUS = false;
extern bool RTC_STATUS = false;
SIM_CONFIG p;

void V2X_CONTROLLER::setup()
{
  if(!vDeserialize(&p))
  {
    vLog("No Configuration Detected");
    vLog("Creating Factory Default Configuration");
    strcpy(p.apn,"www.meditel.ma");
    strcpy(p.broker,"41.140.242.182");
    p.port = 1338;
    p.interval = 5000;
    strcpy(p.gprsPass,"");
    strcpy(p.gprsUser,"");

    vLog("Saving Configuration");
    vSerialize(&p);
  }
  else
  {
    vLog("Configuration Loaded");
  }
}

void V2X_CONTROLLER::loop()
{
  String msg = "";
  if(Serial.available()>0)
  {
    msg = Serial.readString();
    Serial.println("\n>" + msg + "\n");
  }

  V2X_CONTROLLER::rtcTaskHandler(msg);
  V2X_CONTROLLER::networkTaskHandler(msg);
  V2X_CONTROLLER::gpsTaskHandler(msg);
  //V2X_CONTROLLER::pcTaskHandler();
  V2X_CONTROLLER::blinkTaskHandler(msg);
  V2X_CONTROLLER::ioTaskHandler(msg);

  if(msg != "net" && msg != "io" && msg != "rtc" && msg != "blink" && msg != "gps")
    V2X_CONTROLLER::cmdHandler(msg);
}

void V2X_CONTROLLER::cmdHandler(String msg)
{
  if(msg == "ee_length")
    vLog("EEPROM SIZE : "+ String(EEPROM.length()));
  else if (msg == "ee_show")
  {
    vLog("V2X EEPROM");
    for (int i = 0; i < EEPROM.length(); i++)
    {
      Serial.print(String(EEPROM[i],HEX));
    }
    Serial.println();
  }
  else if (msg=="load_cfg")
  {
    vSendConfig(&p);
  }
  else if (msg == "infos")
  {
    vInfo("version","exp-0.1.7a");
    vInfo("netId","exTracker101");
  }
  else if(msg.indexOf("conf#")>=0)
  {
    String payload = "";
    payload = msg.substring(5);
    vSetConfig(&p, payload);
    vLog("Saving Configuration");
    vSerialize(&p);
    vSendConfig(&p);
  }
  else
  {
    if(msg != "")
      vLog("[MAIN] # Undefined Command.");
  }
}

void V2X_CONTROLLER::main(void* p){
  vLog("Controller is Running");

  V2X_CONTROLLER::setup();

  for(;;)
  {
    V2X_CONTROLLER::loop();

    vTaskDelay(1);
  }
}

void V2X_CONTROLLER::pcTaskHandler()
{
  int status = digitalRead(FTDI);
  if(status == 1)
  {
    if(!PC_CONNECTION)
    {
      vLog("Controller Starting PC Task");
      xTaskCreate(V2X_SERIAL_CONNECTOR::main, (const portCHAR *)"PC_TASK", 512, NULL, 2, NULL);
      PC_CONNECTION = true;
    }
  }
  else
  {
    if(PC_CONNECTION)
    {
      vLog("Controller Closing PC TASK");
      PC_CONNECTION = false;
      TaskHandle_t handle = xTaskGetHandle("PC_TASK");
      vTaskDelete(handle);
    }
  }
}

void V2X_CONTROLLER::blinkTaskHandler(String msg)
{
  if(msg == "blink")
  {
    if(BLINK_STATUS)
    {
      vLog("Controller Closing Blink TASK");
      BLINK_STATUS = false;
      TaskHandle_t handle = xTaskGetHandle("BLINK_TASK");
      vTaskDelete(handle);
    }
    else
    {
      vLog("Controller Starting Blink Task");
      xTaskCreate(V2X_BLINK::main, (const portCHAR *)"BLINK_TASK", 128, NULL, 2, NULL);
      BLINK_STATUS = true;
    }
  }
}

void V2X_CONTROLLER::gpsTaskHandler(String msg)
{
  if(msg == "gps")
  {
    if(GPS_STATUS)
    {
      vLog("Controller Closing GPS TASK");
      GPS_STATUS = false;
      TaskHandle_t handle = xTaskGetHandle("GPS_TASK");
      vTaskDelete(handle);
    }
    else
    {
      vLog("Controller Starting GPS TASK");
      xTaskCreate(V2X_GPS::main, (const portCHAR *)"GPS_TASK", 1024, NULL, 2, NULL);
      GPS_STATUS = true;
    }
  }
}

void V2X_CONTROLLER::networkTaskHandler(String msg)
{
  if(msg == "net")
  {
    if(NET_STATUS)
    {
      vLog("Controller Closing NET TASK");
      NET_STATUS = false;
      TaskHandle_t handle = xTaskGetHandle("NET_TASK");
      vTaskDelete(handle);
    }
    else
    {
      vLog("Controller Starting NET TASK");
      while(!Serial2){vLog("waiting for serial2");}
      xTaskCreate(V2X_NETWORK::main, (const portCHAR *)"NET_TASK", 1024, (void*)(&p), 2, NULL);
      NET_STATUS = true;
    }
  }
}

void V2X_CONTROLLER::ioTaskHandler(String msg)
{
  if(msg == "io")
  {
    if(IO_STATUS)
    {
      vLog("Controller Closing IO TASK");
      IO_STATUS = false;
      TaskHandle_t handle = xTaskGetHandle("IO_TASK");
      vTaskDelete(handle);
    }
    else
    {
      vLog("Controller Starting IO TASK");
      xTaskCreate(V2X_SENSORS::main, (const portCHAR *)"IO_TASK", 1024, NULL, 2, NULL);
      IO_STATUS = true;
    }
  }
}

void V2X_CONTROLLER::rtcTaskHandler(String msg)
{
  if(msg == "rtc")
  {
    if(RTC_STATUS)
    {
      vLog("Controller Closing RTC TASK");
      RTC_STATUS = false;
      TaskHandle_t handle = xTaskGetHandle("RTC_TASK");
      vTaskDelete(handle);
    }
    else
    {
      vLog("Controller Starting RTC TASK");
      xTaskCreate(V2X_RTC::main, (const portCHAR *)"RTC_TASK", 1024, NULL, 2, NULL);
      RTC_STATUS = true;
    }
  }
}