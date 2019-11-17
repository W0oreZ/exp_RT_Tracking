#ifndef v2x_network_h
#define v2x_network_h

#define TINY_GSM_MODEM_SIM808
//#define TINY_GSM_DEBUG SerialMon
#define GSM_AUTOBAUD_MIN 115200
#define GSM_AUTOBAUD_MAX 115200

#define DebugSerial Serial
#define NetSerial Serial2

#include "src/vendor/TinyGSM/src/TinyGsmClient.h"
#include "src/vendor/PubSubClient/src/PubSubClient.h"

#include "src/utils/formater/formater.h"

namespace V2X_NETWORK
{
  void main(void* p);

  void setup();
  void loop();
}

void init_Modem();
boolean mqttConnect();
void MessageHandler(char* topic, byte* payload, unsigned int len);
#endif