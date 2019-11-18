#ifndef v2x_io_h
#define v2x_io_h
#include "globals.h"

#define MAX_VOLTAGE_INPUT 15
#define ANALOG_RESOLUTION_UNITS 4096
#define ANALOG_INPUT_UNITS_OFFSET 56

float vAnalogRead(int pin, int offset = 0); // Returns the value of Voltage in V 

bool vDigitalSwitch(int pin); // returns true if it flips

#endif