#include "globals.h"
#include "src/Controller/v2x_controller.h"


void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200);
  while(!Serial);

  vLog("V2X PROGRAME STARTING");
  
  xTaskCreate(V2X_CONTROLLER::main, (const portCHAR *)"CONTROLLER", 1024, NULL, 1, NULL);

  vTaskStartScheduler();
  while(1);
}

void loop()
{

}
