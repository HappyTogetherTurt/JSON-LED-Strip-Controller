#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#include "WifiCredentials.h"
#include "MyWiFi.h"
#include "Handling.h"
#include "ServerDeclaration.h"
#include "MyLeds.h"

void setup()
{
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