#include "globals.h"
HardwareSerial Serial2(PA3, PA2);
HardwareSerial Serial3(PB11, PB10);

#include "src/Controller/v2x_controller.h"


void setup() 
{
  Serial.begin(115200);
  while(!Serial);

  Serial.println("V2X PROGRAME STARTING");
  
  xTaskCreate(V2X_CONTROLLER::main, (const portCHAR *)"CONTROLLER", 512, NULL, 1, NULL);

  vTaskStartScheduler();
  while(1);
}

void loop()
{

}
