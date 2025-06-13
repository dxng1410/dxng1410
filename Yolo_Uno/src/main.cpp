
#include "globals.h"

void setup()
{
  Serial.begin(115200);
  InitWiFi();
  // initDHT20();
  initMQTT();
  // initPIR();
  // InitWebsever();
  initDongCo();
}

void loop()
{
  if (!Wifi_reconnect())
  {
    return;
  }
  reconnectMQTT();
  WebSeverloop();
}

 