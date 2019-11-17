#include "v2x_sensors.h"

void V2X_SENSORS::setup()
{
    IoSerial.println("Sensors");

    pinMode(AI1, INPUT);
    pinMode(AI2, INPUT);
    pinMode(DI1, INPUT);
    pinMode(DI2, INPUT);
    pinMode(DO1, OUTPUT);
    pinMode(DO2, OUTPUT);
}

void V2X_SENSORS::loop()
{
    IoSerial.println("AI1: " + String(analogRead(AI1)));
    IoSerial.println("AI2: " + String(analogRead(AI2)));

    IoSerial.println("DI1: " + String(analogRead(DI1)));
    IoSerial.println("DI2: " + String(analogRead(DI2)));

    vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void V2X_SENSORS::main(void* p)
{
  Serial.println("IO Task Started");
  V2X_SENSORS::setup();

  for(;;)
  {
    V2X_SENSORS::loop();
    vTaskDelay(1);
  }
}
