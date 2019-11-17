#ifndef v2x_sensors_h
#define v2x_sensors_h

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include "STM32FreeRTOSConfig.h"

#define IoSerial Serial

#define AI1 PA4
#define AI2 PA5
#define DI1 PB13
#define DI2 PB13
#define DO1 PB14
#define DO2 PB15
#define WIR PA8

namespace V2X_SENSORS
{
    //core functions
    void main(void* p);
    void setup();
    void loop();
}

#endif