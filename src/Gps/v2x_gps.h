#ifndef v2x_gps_h
#define v2x_gps_h

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include "STM32FreeRTOSConfig.h"

#define TINY_GSM_MODEM_SIM808
//#define TINY_GSM_DEBUG SerialMon
#define GpsSerial Serial2

#include "src/vendor/TinyGSM/src/TinyGsmClient.h"

namespace V2X_GPS
{
  //core functions
  void main(void* p);
  void setup();
  void loop();
}

#endif