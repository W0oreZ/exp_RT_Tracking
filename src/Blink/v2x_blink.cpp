#include "v2x_blink.h"

//STATE VARIABLES
int bInterval; //in seconds

void V2X_BLINK::setup()
{
  pinMode(LED_NET, OUTPUT);
  bInterval = 2;
}

void V2X_BLINK::loop()
{
  digitalWrite(LED_NET, HIGH);
  vTaskDelay((2*1000)/portTICK_PERIOD_MS);
  digitalWrite(LED_NET, LOW);
  vTaskDelay((2*1000)/portTICK_PERIOD_MS);
}

void V2X_BLINK::main(void* p){
  Serial.println("Blink TASK Started !");
  V2X_BLINK::setup();

  for(;;)
  {
    V2X_BLINK::loop();

    vTaskDelay(1);
  }
}