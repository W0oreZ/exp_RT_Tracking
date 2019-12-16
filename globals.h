#ifndef GLOBALS_H
#define GLOBALS_H
#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include "STM32FreeRTOSConfig.h"

#include <SPI.h>
#include <EEPROM.h>
#include "src/vendor/OneWire/OneWire.h"


#define AI1 PA4     //Analog input 1
#define AI2 PA5     //Analog input 2
#define DI1 PB12    //Digital input 1
#define DI2 PB13    //Digital input 2
#define DO1 PB14    //Digital output 1
#define DO2 PB15    //Digital output 2
#define WIR PA8     //RFID
#define FTDI PB6   //PC Connection Digital Detector
#define LED_NET PB3 //Led indicator
#define RFID PA8    //RFID reader
#define SIMPIN PA12 //SIMon/off pin

#define TINY_GSM_MODEM_SIM868     //SIM module Version
//#define TINY_GSM_MODEM_A7         //A7 Module Version
#define GSM_AUTOBAUD_MIN 115200   //BAUDRATE 
#define GSM_AUTOBAUD_MAX 115200   //BAUDRATE

typedef struct SIM_CONFIG
{ 
  char apn[25];
  char gprsUser[15];
  char gprsPass[15];
  char broker[25];
  int port;
  int interval;
} SIM_CONFIG;

#include "src/vendor/Serialization/Serialization.h"
#include "src/utils/pclink/pclink.h"

#endif
