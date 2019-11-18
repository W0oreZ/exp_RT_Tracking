#include "v2x_sensors.h"

bool mstate = false;

void V2X_SENSORS::setup()
{
    IoSerial.println("Sensors");

    pinMode(AI1, INPUT_ANALOG);
    pinMode(AI2, INPUT_ANALOG);
    pinMode(DI1, INPUT);
    pinMode(DI2, INPUT);
    pinMode(DO1, OUTPUT);
    pinMode(DO2, OUTPUT);
}

void V2X_SENSORS::loop()
{
    IoSerial.println("AI1: " + String((analogRead(AI1) << 2) * (15.0 / 4040))); //max value 15V -> 3.255V -> 1010
    //IoSerial.println("AI2: " + String(analogRead(AI2) * (3.3 / 4096.0)));

    //IoSerial.println("DI1: " + String(digitalRead(DI1)));
    //IoSerial.println("DI2: " + String(digitalRead(DI2)));

    /*
    if(mstate)
    {
      digitalWrite(DO1, HIGH);
      digitalWrite(DO2, HIGH);
    }
    else
    {
      digitalWrite(DO1, LOW);
      digitalWrite(DO2, LOW);
    }
    mstate = !mstate;
    */

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
