#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

#include <ESPmDNS.h>

#include "WifiCredentials.h"
#include "MyWiFi.h"

#include "ServerDeclaration.h"
#include "MyLeds.h"
#include "MyTasks.h"

void setup()
{
if(!SPIFFS.begin(true)) {Serial.println("An Error has occurred while mounting SPIFFS");}
preferences.begin("lightsPrefs", false);
MYWIFI::wifiSetup();
Serial.println(MDNS.begin("lamp") ? "mDNS is \"lamp.local\"" : "mDNS setup failed");
pinMode(2, OUTPUT);
pinMode(4, OUTPUT);
ledSetup();
startLedTask();
}

void loop()
{
  delay(1);
}