#ifndef v2x_sensors_h
#define v2x_sensors_h
#include "globals.h"

#include "src/utils/io/io.h"

#define IoSerial Serial

namespace V2X_SENSORS
{
    //core functions
    void main(void* p);
    void setup();
    void loop();
}

#endif