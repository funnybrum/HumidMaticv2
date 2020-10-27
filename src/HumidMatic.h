#pragma once

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>

#include "user_interface.h"

#include "esp8266-base.h"

extern Logger logger;
extern Settings settings;
extern WiFiManager wifi;

#include "BME280.h"
#include "DataCollector.h"
#include "Humidifier.h"

extern BoschBME280 tempSensor;
extern DataCollector dataCollector;
extern Humidifier humidifier;

#define HTTP_PORT 80
#define HOSTNAME "hm-default"