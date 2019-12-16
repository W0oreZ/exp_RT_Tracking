#include "pclink.h"

String jsonDebug(String msg, String type, bool obj = false)
{
  String data = "";
  data +="{\"type\":\"";
  data += type;
  
  if(obj)
  {
    data += "\",\"payload\":"+msg+"}";
  }
  else
  {
    data += "\",\"payload\":\""+msg+"\"}";
  }
  
  return data;
}
String jsonConfig(SIM_CONFIG* conf)
{
  String data = "";
  data +="{\"apn\":\"";
  data += String(conf->apn);
  data += "\",";

  data +="\"broker\":\"";
  data += String(conf->broker);
  data += "\",";

  data +="\"port\":\"";
  data += String(conf->port);
  data += "\",";

  data +="\"interval\":\"";
  data += String(conf->interval);
  data += "\",";

  data +="\"gprsUser\":\"";
  data += String(conf->gprsUser);
  data += "\",";

  data +="\"gprsPass\":\"";
  data += String(conf->gprsPass);
  data += "\"}";

  return data;
}
void vLog(String msg)
{
  Serial.println(jsonDebug(msg,String("LOG")));
}
void vWarn(String msg)
{
  Serial.println(jsonDebug(msg,String("WARN")));
}
void vError(String msg)
{
  Serial.println(jsonDebug(msg,String("ERROR")));
}
void vInfo(String field,String value)
{
  String data = "";
  data += "{\"";
  data += field;
  data += "\":\"";
  data += value;
  data += "\"}";
  Serial.println(jsonDebug(data, String("INFO"), true));
}
void vSendConfig(SIM_CONFIG* conf)
{
  Serial.println(jsonDebug(jsonConfig(conf), String("CONFIG"), true));
}

void vSensorLog(String type, String label, String value)
{
  String data = "";
  data += "{\"type\":\"";
  data += type;
  data += "\",\"label\":\"";
  data += label;
  data += "\",\"value\":\"";
  data += value;
  data += "\"}";
  Serial.println(jsonDebug(data, String("SENSOR"), true));
}

void vSetConfig(SIM_CONFIG* conf, String payload)
{
  StringSplitter newConfig(payload, ',', 6);
  newConfig.getItemAtIndex(0).toCharArray(conf->apn,25);
  newConfig.getItemAtIndex(1).toCharArray(conf->gprsUser,15);
  newConfig.getItemAtIndex(2).toCharArray(conf->gprsPass,15);
  newConfig.getItemAtIndex(3).toCharArray(conf->broker,25);
  conf->port = newConfig.getItemAtIndex(4).toInt();
  conf->interval = newConfig.getItemAtIndex(5).toInt();
}