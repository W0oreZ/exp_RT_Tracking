#ifndef v2x_sensors_h
#define v2x_sensors_h
#include "globals.h"
#include <Wire.h>
#include "src/vendor/OneWire/OneWire.h"

#include "src/utils/io/io.h"

#define IoSerial Serial

namespace V2X_SENSORS
{
    bool rfidRead(String* rfid);
    int writeByte(byte data);
    bool rfidWrite();
    //core functions
    void main(void* p);
    void setup();
    void loop();
}

#endif