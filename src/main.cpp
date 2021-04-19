#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>

#include "WifiCredentials.h"
#include "MyWiFi.h"
#include "Handling.h"
#include "ServerDeclaration.h"
#include "MyLeds.h"
#include "MyTasks.h"

#define EEPROM_SIZE 10

void setup()
{
  EEPROM.begin(EEPROM_SIZE);
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