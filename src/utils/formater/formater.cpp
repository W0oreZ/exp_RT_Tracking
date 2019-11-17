#include"formater.h"

String FORMATER::RAWGPS_TO_JSON(TinyGsm* modem, String imei, bool debug)
{
  String gpsData = "";
  String raw = modem->getGPSraw();

  return gpsData;
}

String FORMATER::GPS_TO_JSON(TinyGsm* modem, String imei, bool debug)
{
  String gpsData = "";
  
  int y,m,d,hh,mm,ss;
  modem->getGPSTime(&y,&m,&d,&hh,&mm,&ss);
  String dt = String(y)+"-"+String(m)+"-"+String(d)+" "+String(hh)+":"+String(mm)+":"+String(ss);
  
  float lat,lng,speed;
  int alt,gsmlev,gpslev;
  modem->getGPS(&lat,&lng,&speed,&alt,&gsmlev,&gpslev);

  gpsData += "{\"imei\":\""+ imei + "\",";
  gpsData += "\"dt\":\""+ dt + "\",";
  gpsData += "\"lat\":"+ String(lat,(unsigned char)10) + ",";
  gpsData += "\"lng\":"+ String(lng,(unsigned char)10) + ",";
  gpsData += "\"speed\":"+ String(speed) + ",";
  gpsData += "\"alt\":"+ String(alt) + ",";
  gpsData += "\"gsmlev\":"+ String(gsmlev) + ",";
  gpsData += "\"gpslev\":"+ String(gpslev) + "}";

  return gpsData;
}