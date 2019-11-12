#ifndef v2x_gps_h
#define v2x_gps_h

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include "STM32FreeRTOSConfig.h"

namespace V2X_GPS
{
  //core functions
  void main(void* p);
  void setup();
  void loop();
}

#endif