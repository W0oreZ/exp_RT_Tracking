#ifndef SPIEEPROM_h
#define SPIEEPROM_h

#include "globals.h"

#define SLAVESELECT PA15 // SPI SS Pin
                       // on MEGA2560 should be PIN 53
					   // change it if you want to use another pin

//opcodes
#define WREN  6
#define WRDI  4
#define RDSR  5
#define WRSR  1
#define READ  3
#define WRITE 2

class SPIEEPROM
{
  private:
	byte eeprom_type;
	
	
	void send_address(long addr);
	void start_write();
	bool isWIP(); // is write in progress?
	
  public:
	SPIEEPROM(); 		  // default to type 0
    SPIEEPROM(byte type); // type=0: 16-bits address
						  // type=1: 24-bits address
						  // type>1: defaults to type 0	
	void begin();

	template <typename T> T &write(long addr, T &value)
	{
	    byte *p = (byte*) &value;
	    start_write(); // send WRITE command
		send_address(addr); // send address
	    unsigned int i;
	    for (i = 0; i < sizeof(value); i++) 
	    {
	    	SPI.transfer(*p++);
	    }
		digitalWrite(SLAVESELECT,HIGH);
		while (isWIP()) {	
			delay(1);
		}  
	    digitalWrite(SLAVESELECT,HIGH);
	}

	template <typename T> T &read(long addr, T &value)
	{	
	    byte* p = (byte*)(void*)&value;
	    digitalWrite(SLAVESELECT,LOW);
		SPI.transfer(READ); // send READ command
		send_address(addr); // send address
    	unsigned int i;
    	for (i = 0; i < sizeof(value); i++) 
    	{
    		*p++ = SPI.transfer(0xFF);
		}
    	digitalWrite(SLAVESELECT,HIGH); //release chip, signal end transfer 
	}
};

#endif // SPIEEPROM_h
