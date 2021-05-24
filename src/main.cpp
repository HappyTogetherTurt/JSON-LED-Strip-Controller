#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include <EEPROM.h>
//#include <ESPmDNS.h>

#include "WifiCredentials.h"
#include "MyWiFi.h"
#include "Handling.h"
#include "ServerDeclaration.h"
#include "MyLeds.h"
#include "MyTasks.h"

#define EEPROM_SIZE 5

void setup()
{
if(!SPIFFS.begin(true)) {Serial.println("An Error has occurred while mounting SPIFFS");}
EEPROM.begin(EEPROM_SIZE);
//if(!MDNS.begin("lights")) {Serial.println("An Error has occurred while beginning mDNS");}
MYWIFI::wifiSetup();
pinMode(2, OUTPUT);
pinMode(4, OUTPUT);
ledSetup();
startLedTask();
}

void loop()
{
  server.handleClient();
  delay(1);
}