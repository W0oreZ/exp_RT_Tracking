#ifndef v2x_controller_h
#define v2x_controller_h

#include "globals.h"

#include "src/Network/v2x_network.h"
#include "src/Gps/v2x_gps.h"
#include "src/SerialConnector/v2x_serial_connector.h"
#include "src/Blink/v2x_blink.h"
#include "src/Sensors/v2x_sensors.h"

namespace V2X_CONTROLLER
{
  //Controller Methods
  void InitPcTask();
  void pcTaskHandler();
  void blinkTaskHandler(String msg);
  void gpsTaskHandler(String msg);
  void networkTaskHandler(String msg);
  void ioTaskHandler(String msg);
  
  //TASK CORE FUNCTIONS
  void main(void* p);
  void setup();
  void loop();
}

#endif