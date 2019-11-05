#include "globals.h"
#include "src/Network/v2x_network.h"
#include "src/Blink/v2x_blink.h"

void setup() 
{
  DebugSerial.begin(115200);
  NetSerial.begin(115200);
  while(!NetSerial){;}
  
  xTaskCreate(V2X_NETWORK::main, (const portCHAR *)"NET_TASK", 2048, NULL, 2, &v2x_network_handler);
  xTaskCreate(V2X_BLINK::main, (const portCHAR *)"BLINK_TASK", 128, NULL, 2, &v2x_blink_handler);

  vTaskStartScheduler();
  while(1);
}

void loop()
{

}
