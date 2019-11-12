#include "v2x_gps.h"

void V2X_GPS::setup()
{
  
}

void V2X_GPS::loop()
{

}

void V2X_GPS::main(void* p)
{
  Serial.println("GPS Task Started");
  V2X_GPS::setup();

  for(;;)
  {
    V2X_GPS::loop();
    vTaskDelay(1);
  }
}