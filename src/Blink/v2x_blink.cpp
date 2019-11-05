#include "src/Blink/v2x_blink.h"
#include <Arduino.h>
#include <STM32FreeRTOS.h>

void V2X_BLINK::setup()
{
  Serial.println("BLINK TASK Started !");
  pinMode(LED_NET, OUTPUT);
}

void V2X_BLINK::loop()
{
  digitalWrite(LED_NET, HIGH);
  vTaskDelay(500 / portTICK_PERIOD_MS );
  digitalWrite(LED_NET, LOW);
  vTaskDelay(500 / portTICK_PERIOD_MS );
}

void V2X_BLINK::main(void* p){
  V2X_BLINK::setup();

  for(;;)
  {
    V2X_BLINK::loop();

    vTaskDelay(1);
  }
}