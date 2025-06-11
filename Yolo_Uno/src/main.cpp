
#include "globals.h"

void setup()
{
  Serial.begin(115200);
  initDHT20();
  initMQTT();
  initPIR();
}

void loop()
{
  if (!Wifi_reconnect())
  {
    return;
  }
  reconnectMQTT();
  // getValueDHT20();
  // getValuePIR();
  delay(2000);
}

 