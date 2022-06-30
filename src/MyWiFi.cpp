#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <Update.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <Preferences.h>

#include "MyWifi.h"
#include "ServerDeclaration.h"

#include "MyLeds.h"

String ip2Str(IPAddress ip)
{
    String s = "";
    for (int i = 0; i < 4; i++)
    {
        s += i ? "." + String(ip[i]) : String(ip[i]);
    }
    return s;
}

String processor(const String &var)
{
    /*Serial.println(var);
    if (var == "IP")
    {
        return ip2Str(WiFi.localIP());
    }*/
    return String();
}

void wifiSetup()
{
    WiFi.mode(WIFI_STA);
    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    uint8_t i = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(500);

        if ((++i % 16) == 0)
        {
            Serial.println(F(" still trying to connect"));
        }
    }

    Serial.print(F("Connected. My IP address is: "));
    Serial.println(WiFi.localIP());

    server.begin();

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/controller.html", String(), false, processor);
                  response->addHeader("Access-Control-Allow-Origin", "*");
                  request->send(response);
              });

    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/favicon.ico"); });

    server.on("/test", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  request->send_P(200, "application/json", "{\"status\":\"TEST_RECIEVED\"}");
                  Serial.println(preferences.getInt("red"));
                  Serial.println(preferences.getInt("green"));
                  Serial.println(preferences.getInt("blue"));
              });

    server.on(
        "/mode", HTTP_PUT, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        {
            Serial.println("Mode");
            AsyncWebServerResponse *response = request->beginResponse(200, "application/json", "{\"status\":\"MODE_RECIEVED\"}");
            response->addHeader("Access-Control-Allow-Origin", "*");
            request->send(response);
            char json[len + 1];
            for (size_t i = 0; i < len; i++)
            {
                json[i] = (char)data[i];
            }
            json[len] = '\0';
            StaticJsonDocument<20> doc;
            deserializeJson(doc, json);
            preferences.putInt("mode", doc["mode"]);
            preferences.putInt("red", MYLEDS::data[MANUAL_RED]);
            preferences.putInt("green", MYLEDS::data[MANUAL_GREEN]);
            preferences.putInt("blue", MYLEDS::data[MANUAL_BLUE]);
            preferences.end();
            ESP.restart();
        });

    server.on(
        "/rgb", HTTP_PUT, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        {
            request->send_P(200, "application/json", "{\"status\":\"RGB_RECIEVED\"}");
            char json[len + 1];
            for (size_t i = 0; i < len; i++)
            {
                json[i] = (char)data[i];
            }
            json[len] = '\0';
            StaticJsonDocument<50> doc;
            deserializeJson(doc, json);

            if (doc["red"] != 256)
            {
                MYLEDS::data[MANUAL_RED] = doc["red"];
            }
            if (doc["green"] != 256)
            {
                MYLEDS::data[MANUAL_GREEN] = doc["green"];
            }
            if (doc["blue"] != 256)
            {
                MYLEDS::data[MANUAL_BLUE] = doc["blue"];
            }
        });

    server.on(
        "/breathe", HTTP_PUT, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        {
            request->send_P(200, "application/json", "{\"status\":\"BREATHE_RECIEVED\"}");
            char json[len + 1];
            for (size_t i = 0; i < len; i++)
            {
                json[i] = (char)data[i];
            }
            json[len] = '\0';
            StaticJsonDocument<25> doc;
            deserializeJson(doc, json);

            MYLEDS::data[BREATHE_DELAY] = doc["breatheSpeed"];
        });

    server.on(
        "/chaser", HTTP_PUT, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        {
            request->send_P(200, "application/json", "{\"status\":\"CHASER_RECIEVED\"}");
            char json[len + 1];
            for (size_t i = 0; i < len; i++)
            {
                json[i] = (char)data[i];
            }
            json[len] = '\0';
            StaticJsonDocument<25> doc;
            deserializeJson(doc, json);

            MYLEDS::data[CHASER_DELAY] = doc["chaserSpeed"];
        });

    server.on(
        "/flow", HTTP_PUT, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        {
            request->send_P(200, "application/json", "{\"status\":\"FLOW_RECIEVED\"}");
            char json[len + 1];
            for (size_t i = 0; i < len; i++)
            {
                json[i] = (char)data[i];
            }
            json[len] = '\0';
            StaticJsonDocument<25> doc;
            deserializeJson(doc, json);

            MYLEDS::data[FLOW_DELAY] = doc["flowSpeed"];
        });

    server.on(
        "/ember", HTTP_PUT, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        {
            request->send_P(200, "application/json", "{\"status\":\"EMBER_RECIEVED\"}");
            char json[len + 1];
            for (size_t i = 0; i < len; i++)
            {
                json[i] = (char)data[i];
            }
            json[len] = '\0';
            StaticJsonDocument<25> doc;
            deserializeJson(doc, json);

            MYLEDS::data[EMBER_DELAY] = doc["emberSpeed"];
        });

    server.on(
        "/update", HTTP_POST, [](AsyncWebServerRequest *request) {}, [](AsyncWebServerRequest *request, const String &filename, size_t index, uint8_t *data, size_t len, bool final)
        {
            if (!index)
            {
                Serial.println("Update");
                size_t content_len = request->contentLength();
                // if filename includes spiffs, update the spiffs partition
                int cmd = (filename.indexOf("spiffs") > -1) ? U_SPIFFS : U_FLASH;
                if (!Update.begin(UPDATE_SIZE_UNKNOWN, cmd))
                {
                    Update.printError(Serial);
                }
            }

            if (Update.write(data, len) != len)
            {
                Update.printError(Serial);
            }

            if (final)
            {
                AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "Please wait while the device reboots");
                response->addHeader("Refresh", "20");
                response->addHeader("Location", "/");
                request->send(response);
                if (!Update.end(true))
                {
                    Update.printError(Serial);
                }
                else
                {
                    Serial.println("Update complete");
                    Serial.flush();
                    ESP.restart();
                }
            }
        });
}
