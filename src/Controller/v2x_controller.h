#ifndef v2x_controller_h
#define v2x_controller_h

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include "STM32FreeRTOSConfig.h"

#include "src/SerialConnector/v2x_serial_connector.h"
#include "src/Blink/v2x_blink.h"

#define FTDI PA15

namespace V2X_CONTROLLER
{
  //Controller Methods
  void InitPcTask();
  void pcTaskHandler();
  void blinkTaskHandler();
  
  //TASK CORE FUNCTIONS
  void main(void* p);
  void setup();
  void loop();
}

#endif