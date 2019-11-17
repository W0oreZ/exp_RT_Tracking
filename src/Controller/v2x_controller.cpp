#include "v2x_controller.h"

//STATE VARIABLES
bool PC_CONNECTION;
bool BLINK_STATUS = false;
bool GPS_STATUS = false;
bool NET_STATUS = false;
bool IO_STATUS = false;

void V2X_CONTROLLER::setup()
{
  //V2X_CONTROLLER::InitPcTask();
}

void V2X_CONTROLLER::loop()
{
  String msg = "";
  if(Serial.available()>0)
  {
    msg = Serial.readString();
    Serial.println("Received : " + msg);
  }

  //V2X_CONTROLLER::networkTaskHandler(msg);
  //V2X_CONTROLLER::gpsTaskHandler(msg);
  //V2X_CONTROLLER::pcTaskHandler();
  //V2X_CONTROLLER::blinkTaskHandler(msg);
  V2X_CONTROLLER::ioTaskHandler(msg);
}

void V2X_CONTROLLER::main(void* p){
  Serial.println("Controller is Running");

  V2X_CONTROLLER::setup();

  for(;;)
  {
    V2X_CONTROLLER::loop();

    vTaskDelay(1);
  }
}

void V2X_CONTROLLER::InitPcTask()
{
  PC_CONNECTION = false;
  pinMode(FTDI, INPUT);
}

void V2X_CONTROLLER::pcTaskHandler()
{
  int status = digitalRead(FTDI);
  if(status == 1)
  {
    if(!PC_CONNECTION)
    {
      Serial.println("Controller Starting PC Task");
      xTaskCreate(V2X_SERIAL_CONNECTOR::main, (const portCHAR *)"PC_TASK", 512, NULL, 2, NULL);
      PC_CONNECTION = true;
    }
  }
  else
  {
    if(PC_CONNECTION)
    {
      Serial.println("Controller Closing PC TASK");
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
      Serial.println("Controller Closing Blink TASK");
      BLINK_STATUS = false;
      TaskHandle_t handle = xTaskGetHandle("BLINK_TASK");
      vTaskDelete(handle);
    }
    else
    {
      Serial.println("Controller Starting Blink Task");
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
      Serial.println("Controller Closing GPS TASK");
      GPS_STATUS = false;
      TaskHandle_t handle = xTaskGetHandle("GPS_TASK");
      vTaskDelete(handle);
    }
    else
    {
      Serial.println("Controller Starting GPS TASK");
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
      Serial.println("Controller Closing NET TASK");
      NET_STATUS = false;
      TaskHandle_t handle = xTaskGetHandle("NET_TASK");
      vTaskDelete(handle);
    }
    else
    {
      Serial.println("Controller Starting NET TASK");
      Serial2.begin(115200);
      while(!Serial2);
      xTaskCreate(V2X_NETWORK::main, (const portCHAR *)"NET_TASK", 2048, NULL, 2, NULL);
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
      Serial.println("Controller Closing IO TASK");
      IO_STATUS = false;
      TaskHandle_t handle = xTaskGetHandle("IO_TASK");
      vTaskDelete(handle);
    }
    else
    {
      Serial.println("Controller Starting IO TASK");
      xTaskCreate(V2X_SENSORS::main, (const portCHAR *)"IO_TASK", 128, NULL, 2, NULL);
      IO_STATUS = true;
    }
  }
}