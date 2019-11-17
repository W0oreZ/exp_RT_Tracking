#ifndef FORMATER_h
#define FORMATER_h

#define TINY_GSM_MODEM_SIM808
#include<Arduino.h>
#include "src/vendor/TinyGSM/src/TinyGsmClient.h"

namespace FORMATER
{
  String RAWGPS_TO_JSON(TinyGsm* modem, String imei, bool debug = false);
  String GPS_TO_JSON(TinyGsm* modem, String imei, bool debug = false);
}

#endif