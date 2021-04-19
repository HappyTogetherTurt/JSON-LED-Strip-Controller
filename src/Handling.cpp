#include <Arduino.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <Esp.h>

#include "Handling.h"
#include "ServerDeclaration.h"
#include "MyLeds.h"

void test()
{
    String str = String(EEPROM.read(MODE_ADDRESS));
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", str);
    for (unsigned int i = 0; i <= 9; i++)
    {
        digitalWrite(2, HIGH);
        delay(100);
        digitalWrite(2, LOW);
        delay(100);
    }
}

void modeHandle()
{

    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "OK");

    StaticJsonDocument<25> doc;
    deserializeJson(doc, server.arg("plain"));

    EEPROM.write(MODE_ADDRESS, doc["mode"]);
    EEPROM.commit();
    delay(500);
    ESP.restart();
}

void manualHandle()
{
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "OK");

    StaticJsonDocument<96> doc;
    deserializeJson(doc, server.arg("plain"));

    data[MANUAL_RED] = doc["red"];
    data[MANUAL_GREEN] = doc["green"];
    data[MANUAL_BLUE] = doc["blue"];
}

void rainbowchaserHandle()
{
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "OK");

    StaticJsonDocument<25> doc;
    deserializeJson(doc, server.arg("plain"));

    data[RAINBOW_CHASER_SPEED] = doc["rainbowChaserSpeed"];
}

void flowHandle()
{
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "OK");

    StaticJsonDocument<25> doc;
    deserializeJson(doc, server.arg("plain"));

    data[FLOW_SPEED] = doc["flowSpeed"];
}

void christmasHandle()
{
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "OK");

    StaticJsonDocument<25> doc;
    deserializeJson(doc, server.arg("plain"));

    data[CHRISTMAS_SPEED] = doc["chrstmasSpeed"];
}