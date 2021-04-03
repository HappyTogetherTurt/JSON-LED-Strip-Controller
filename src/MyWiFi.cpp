#include "MyWifi.h"
#include "ServerDeclaration.h"
#include "Handling.h"


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

    server.on("/test", HTTP_GET, test);
}

