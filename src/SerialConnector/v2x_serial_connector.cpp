#include "v2x_serial_connector.h"
extern TaskHandle_t v2x_pc_handler = NULL;

String msg = "";
void V2X_SERIAL_CONNECTOR::setup()
{
  CONSOLE.begin(115200);
  while(!CONSOLE){;}
  
  CONSOLE.println("Connection to PC Started !");
}

void V2X_SERIAL_CONNECTOR::loop()
{
  while(CONSOLE.available()>0)
  {
    msg = CONSOLE.readString();
  }

  if(msg != "")
  {
    CONSOLE.println("Received : "+ msg);
    msg = "";
  }

  //vTaskDelay(1000 / portTICK_PERIOD_MS );
}

void V2X_SERIAL_CONNECTOR::main(void* p){
  Serial.println("PC TASK Started !");

  V2X_SERIAL_CONNECTOR::setup();

  for(;;)
  {
    V2X_SERIAL_CONNECTOR::loop();

    vTaskDelay(1);
  }
}