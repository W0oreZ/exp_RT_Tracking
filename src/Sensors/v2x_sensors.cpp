#include "v2x_sensors.h"

OneWire ibutton(RFID);

byte address[8];
String rf = "00 00 00 00 00 00 00";

void V2X_SENSORS::setup()
{
	pinMode(FTDI, INPUT);
	pinMode(AI1, INPUT_ANALOG);
	pinMode(AI2, INPUT_ANALOG);
	pinMode(DI1, INPUT);
	pinMode(DI2, INPUT);
	pinMode(DO1, OUTPUT);
	pinMode(DO2, OUTPUT);
}

void V2X_SENSORS::loop()
{
	if(!V2X_SENSORS::rfidRead(&rf))
	{
		rf = "00 00 00 00 00 00 00";
	}
	
	vSensorLog("ANALOGIQUE","ai1",String(vAnalogRead(AI1)));
	vSensorLog("ANALOGIQUE","ai2",String(vAnalogRead(AI2)));
	vSensorLog("DIGITAL","di1",String(vAnalogRead(DI1)));
	vSensorLog("DIGITAL","di2",String(vAnalogRead(DI2)));
	vSensorLog("RFID","rfid",rf);

  vTaskDelay(1000);
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

bool V2X_SENSORS::rfidRead(String* rfid)
{
  if (!ibutton.search(address)){
		ibutton.reset_search();
		return false;
	}
  else
  {
    *rfid = "";
	  for (byte x = 7; x>0; x--){  
      if (address[x]<16) {
        *rfid += "0";
      }
      *rfid += String(address[x],HEX)+" ";
	  }
    ibutton.reset_search();
    
    return true;
  }
}

bool V2X_SENSORS::rfidWrite()
{
  ibutton.skip(); 
  ibutton.reset(); 
  ibutton.write(0x33);
	Serial.print("ID before write:");
	for (byte x=0; x<8; x++){
		Serial.print(' ');
		Serial.print(ibutton.read(), HEX);
	}
	
	ibutton.skip();
	ibutton.reset();
	ibutton.write(0xD1);

  digitalWrite(RFID, LOW); pinMode(RFID, OUTPUT); vTaskDelay(60/1000);
	pinMode(RFID, INPUT); digitalWrite(RFID, HIGH); vTaskDelay(10);

	byte newID[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
					 
	ibutton.skip();
	ibutton.reset();
	ibutton.write(0xD5);
	
	for (byte x = 0; x<8; x++){
		writeByte(newID[x]);
		Serial.print('*');
	}
	Serial.print('\n');
	
	ibutton.reset();
	ibutton.write(0xD1);

  digitalWrite(RFID, LOW); pinMode(RFID, OUTPUT); vTaskDelay(60/1000);
	pinMode(RFID, INPUT); digitalWrite(RFID, HIGH); vTaskDelay(10);

}

int V2X_SENSORS::writeByte(byte data){
	for (byte data_bit=0; data_bit<8; data_bit++) {
		if (data & 1) {
			digitalWrite(RFID, LOW); pinMode(RFID, OUTPUT);
			delayMicroseconds(60);
			pinMode(RFID, INPUT); digitalWrite(RFID, HIGH);
			delay(10);
		} else {
			digitalWrite(RFID, LOW); pinMode(RFID, OUTPUT);
			pinMode(RFID, INPUT); digitalWrite(RFID, HIGH);
			delay(10);
		}
		data = data >> 1;
	}
	return 0;
}