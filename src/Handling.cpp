#include <Arduino.h>
#include <ArduinoJson.h>
<<<<<<< HEAD
#include <EEPROM.h>
#include <Esp.h>
=======
#include <SPIFFS.h>
#include <EEPROM.h>
>>>>>>> 04c89170e6d9fe92b9779a399efd53a15a70db11

#include "Handling.h"
#include "ServerDeclaration.h"
#include "MyLeds.h"

void handleIndexPage()
{
    Serial.println(modeVar);
    String uri;
    switch (modeVar)
    {
    case UPDATE:
        uri = "/update.html";
        break;

    case MANUAL:
        uri = "/manual.html";
        break;

    case BREATHE:
        uri = "/breathe.html";
        break;

    case RAINBOW_CHASER:
        uri = "/rainbowchaser.html";
        break;

    case FLOW:
        uri = "/flow.html";
        break;

    case CHRISTMAS:
        uri = "/christmas.html";
        break;

    default:
        uri = "/uhoh.html";
        break;
    }
    File file = SPIFFS.open(uri, "r");
    String fileAsString;
    while (file.available())
    {
        fileAsString += (char)file.read();
    }
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", fileAsString);
}

void handleManualPage()
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
}

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

<<<<<<< HEAD
    data[RAINBOW_CHASER_SPEED] = doc["rainbowChaserSpeed"];
=======
    data[RAINBOW_CHASER_DELAY] = doc["rainbowChaserSpeed"];
>>>>>>> 04c89170e6d9fe92b9779a399efd53a15a70db11
}

void flowHandle()
{
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "OK");

    StaticJsonDocument<25> doc;
    deserializeJson(doc, server.arg("plain"));

<<<<<<< HEAD
    data[FLOW_SPEED] = doc["flowSpeed"];
=======
    data[FLOW_DELAY] = doc["flowSpeed"];
>>>>>>> 04c89170e6d9fe92b9779a399efd53a15a70db11
}

void christmasHandle()
{
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "OK");

    StaticJsonDocument<25> doc;
    deserializeJson(doc, server.arg("plain"));

<<<<<<< HEAD
    data[CHRISTMAS_SPEED] = doc["chrstmasSpeed"];
=======
    data[CHRISTMAS_DELAY] = doc["chrstmasSpeed"];
>>>>>>> 04c89170e6d9fe92b9779a399efd53a15a70db11
}