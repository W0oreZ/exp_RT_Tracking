#ifndef v2x_blink_h
#define v2x_blink_h

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include "STM32FreeRTOSConfig.h"

#define LED_NET PB3

namespace V2X_BLINK
{

  //TASK CORE FUNCTIONS
  void main(void* p);
  void setup();
  void loop();
}

#endif