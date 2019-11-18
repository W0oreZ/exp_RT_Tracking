#ifndef v2x_gps_h
#define v2x_gps_h

#include "globals.h"
#include "src/vendor/TinyGSM/src/TinyGsmClient.h"

#define GpsSerial Serial2

namespace V2X_GPS
{
  //core functions
  void main(void* p);
  void setup();
  void loop();
}

#endif