#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
<<<<<<< HEAD
#include <EEPROM.h>
=======
#include <SPIFFS.h>
//#include <ESPmDNS.h>
>>>>>>> 04c89170e6d9fe92b9779a399efd53a15a70db11

#include "WifiCredentials.h"
#include "MyWiFi.h"
#include "Handling.h"
#include "ServerDeclaration.h"
#include "MyLeds.h"
#include "MyTasks.h"

#define EEPROM_SIZE 10

void setup()
{
<<<<<<< HEAD
  EEPROM.begin(EEPROM_SIZE);
  MYWIFI::wifiSetup();
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  ledSetup();
  startLedTask();
  
=======
if(!SPIFFS.begin(true)) {Serial.println("An Error has occurred while mounting SPIFFS");}
//if(!MDNS.begin("lights")) {Serial.println("An Error has occurred while beginning mDNS");}
MYWIFI::wifiSetup();
pinMode(2, OUTPUT);
pinMode(4, OUTPUT);
ledSetup();
>>>>>>> 04c89170e6d9fe92b9779a399efd53a15a70db11
}

void loop()
{
  server.handleClient();
  delay(1);
}