#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
//#include <ESPmDNS.h>

#include "WifiCredentials.h"
#include "MyWiFi.h"
#include "Handling.h"
#include "ServerDeclaration.h"
#include "MyLeds.h"

void setup()
{
if(!SPIFFS.begin(true)) {Serial.println("An Error has occurred while mounting SPIFFS");}
//if(!MDNS.begin("lights")) {Serial.println("An Error has occurred while beginning mDNS");}
MYWIFI::wifiSetup();
pinMode(2, OUTPUT);
pinMode(4, OUTPUT);
ledSetup();
}

void loop()
{
  server.handleClient();
  delay(1);
}