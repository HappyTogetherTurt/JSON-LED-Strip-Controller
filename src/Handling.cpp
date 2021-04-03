#include <Arduino.h>
#include <ArduinoJson.h>

#include "Handling.h"
#include "ServerDeclaration.h"
#include "MyLeds.h"

void test()
{
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "TEST_OK");
    for (unsigned int i = 0; i <= 9; i++)
    {
        digitalWrite(2, HIGH);
        delay(100);
        digitalWrite(2, LOW);
        delay(100);
    }
}

void mode()
{
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "OK");
}

void manualHandle()
{
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "OK");

    StaticJsonDocument<96> doc;
    deserializeJson(doc, server.arg("plain"));

    for (int i = 0; i <= 2; i++)
    {
        data[i] = doc["rgb"][i];
    }
}