#ifndef GLOBALS_H
#define GLOBALS_H
#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include "STM32FreeRTOSConfig.h"

#define AI1 PA4     //Analog input 1
#define AI2 PA5     //Analog input 2
#define DI1 PB12    //Digital input 1
#define DI2 PB13    //Digital input 2
#define DO1 PB14    //Digital output 1
#define DO2 PB15    //Digital output 2
#define WIR PA8     //RFID
#define FTDI PA15   //PC Connection Digital Detector
#define LED_NET PB3 //Led indicator

#define TINY_GSM_MODEM_SIM808     //SIM module Version
#define GSM_AUTOBAUD_MIN 115200   //BAUDRATE 
#define GSM_AUTOBAUD_MAX 115200   //BAUDRATE

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
