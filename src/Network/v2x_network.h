#ifndef v2x_network_h
#define v2x_network_h
#include "globals.h"

#include "src/vendor/TinyGSM/src/TinyGsmClient.h"
#include "src/vendor/PubSubClient/src/PubSubClient.h"

#include "src/utils/formater/formater.h"

#define DebugSerial Serial
#define NetSerial Serial2

namespace V2X_NETWORK
{
  void main(void* p);

  void setup(SIM_CONFIG* conf);
  void loop();
}

void init_Modem();
boolean mqttConnect();
void MessageHandler(char* topic, byte* payload, unsigned int len);
#endif