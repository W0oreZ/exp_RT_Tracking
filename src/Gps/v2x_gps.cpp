#include "v2x_gps.h"

TinyGsm sim(GpsSerial);

void V2X_GPS::setup()
{
  //GpsSerial.begin(115200);
  //while(!GpsSerial);

  Serial.print("Modem Info: ");
  Serial.println(sim.getModemInfo());
  sim.enableGPS();
  
}

void V2X_GPS::loop()
{
  String pos = sim.getGPSraw();
  Serial.print("GPS : ");
  Serial.println(pos);
  vTaskDelay(5000);
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