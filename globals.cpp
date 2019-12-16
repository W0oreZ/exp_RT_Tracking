#include <globals.h>

extern HardwareSerial Serial2(PA3, PA2);//serial1 arduino SIM module
extern HardwareSerial Serial3(PB11, PB10);//serial2 pc connection

extern SPIClass mySPI(PB5, PB4, PB3);