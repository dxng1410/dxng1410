#ifndef GLOBALS_H
#define GLOBALS_H

// include libraries
#include <Wire.h>
#include <WiFi.h>
#include <DHT20.h>
#include <PubSubClient.h>
#include<PIR.h>
#include <WebServer.h>

///
#include "../src/connect/TaskWifi.h"
#include "../src/connect/TaskMQTT.h"
#include "../src/connect/TaskWebSever.h"

#include "../src/device/TaskDHT20.h"
#include "../src/device/TaskPIRsensor.h"
#include "../src/device/TaskDongCo.h"
#include "../src/device/TaskRGB.h"

#endif