#ifndef FORMATER_h
#define FORMATER_h

#include "globals.h"
#include "src/vendor/TinyGSM/src/TinyGsmClient.h"

namespace FORMATER
{
  String RAWGPS_TO_JSON(TinyGsm* modem, String imei, bool debug = false);
  String GPS_TO_JSON(TinyGsm* modem, String imei, bool debug = false);
}

#endif