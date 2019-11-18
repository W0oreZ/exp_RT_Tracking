#ifndef GLOBALS_H
#define GLOBALS_H
#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include "STM32FreeRTOSConfig.h"



struct SIM_CONFIG
{ 
  char* apn;
  char* gprsUser;
  char* gprsPass;
  char* broker;
  int port;
  long interval;
};

#endif
