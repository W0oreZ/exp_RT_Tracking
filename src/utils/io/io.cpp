#include "io.h"

float vAnalogRead(int pin)
{
  unsigned int value = (analogRead(pin) << 2);
  float result = value * ((float)MAX_VOLTAGE_INPUT/(ANALOG_RESOLUTION_UNITS-ANALOG_INPUT_UNITS_OFFSET));
  return result;
}

bool vDigitalSwitch(int pin)
{
  if(digitalRead(pin) == HIGH)
  {
    digitalWrite(pin,LOW);
    return true;
  }
  
  if(digitalRead(pin) == LOW)
  {
    digitalWrite(pin,HIGH);
    return true;
  }

  return false;
}