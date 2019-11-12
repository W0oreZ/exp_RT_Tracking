#include "v2x_controller.h"

//STATE VARIABLES
bool PC_CONNECTION;
bool BLINK_STATUS = false;

void V2X_CONTROLLER::setup()
{
  V2X_CONTROLLER::InitPcTask();
}

void V2X_CONTROLLER::loop()
{
  V2X_CONTROLLER::pcTaskHandler();
  V2X_CONTROLLER::blinkTaskHandler();
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

void V2X_CONTROLLER::blinkTaskHandler()
{
  String msg;
  if(Serial.available()>0)
  {
    msg = Serial.readString();
  }

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