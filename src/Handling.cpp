#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <EEPROM.h>

#include "Handling.h"
#include "ServerDeclaration.h"
#include "MyLeds.h"

void handleIndexPage()
{
    Serial.println(modeVar);
    File file = SPIFFS.open("/controller.html", "r");
    String fileAsString;
    while (file.available())
    {
        fileAsString += (char)file.read();
    }
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", fileAsString);
}

/*void handleManualPage()
{
    File file = SPIFFS.open("/manual.html", "r");
    String fileAsString;
    while (file.available())
    {
        fileAsString += (char)file.read();
    }
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", fileAsString);
}

void handleEasyHTTP()
{
    File file = SPIFFS.open("/EasyHTTP.js", "r");
    String fileAsString;
    while (file.available())
    {
        fileAsString += (char)file.read();
    }
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", fileAsString);
}*/

void test()
{
    String str = String(EEPROM.read(MODE_ADDRESS));
    server.sendHeader("Connection", "close");
    String _ = String(data[0]) + String(data[1]) + String(data[2]) + String(data[3]) + String(data[4]);
    server.send(200, "text/plain", _);
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
    server.send(200, "application/json", "{\"status\":\"MODE_RECIEVED\"}");

    Serial.println(server.arg("plain"));

    StaticJsonDocument<25> doc;
    deserializeJson(doc, server.arg("plain"));

    EEPROM.write(MODE_ADDRESS, doc["mode"]);
    for (int i = 1; i <= 8; i++)
    {
        EEPROM.write(i, data[i - 1]);
    }
    EEPROM.commit();
    ESP.restart();
}

void manualHandle()
{
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "OK");

    StaticJsonDocument<96> doc;
    deserializeJson(doc, server.arg("plain"));

    if (doc["red"] != 256)
    {
        data[MANUAL_RED] = doc["red"];
    }
    if (doc["green"] != 256)
    {
        data[MANUAL_GREEN] = doc["green"];
    }
    if (doc["blue"] != 256)
    {
        data[MANUAL_BLUE] = doc["blue"];
    }
}

void rainbowchaserHandle()
{
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "OK");

    StaticJsonDocument<40> doc;
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

    StaticJsonDocument<40> doc;
    deserializeJson(doc, server.arg("plain"));

    data[CHRISTMAS_DELAY] = doc["christmasSpeed"];
}