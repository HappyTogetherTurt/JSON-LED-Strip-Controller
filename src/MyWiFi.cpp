<<<<<<< HEAD
#include <Update.h>
=======
#include <WebServer.h>
#include <Update.h>
#include <SPIFFS.h>
>>>>>>> 04c89170e6d9fe92b9779a399efd53a15a70db11

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

    server.on("/", HTTP_GET, handleIndexPage);

    server.on("/test", HTTP_GET, test);
<<<<<<< HEAD
    server.on("/mode", HTTP_PUT, modeHandle);
    server.on("/manual", HTTP_PUT, manualHandle);
    server.on("/rainbowchaser", HTTP_PUT, rainbowchaserHandle);

    #pragma region
    server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });
  #pragma endregion
=======
    server.on("/mode",HTTP_PUT, modeHandle);
    server.on("/rgb", HTTP_PUT, manualHandle);
    server.on("/rainbowChaser", HTTP_PUT, rainbowchaserHandle);
    server.on("/flow", HTTP_PUT, flowHandle);
    server.on("/christmas", HTTP_PUT, christmasHandle);
    
    server.on(
        "/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart(); }, []() {
            HTTPUpload &upload = server.upload();
            if (upload.status == UPLOAD_FILE_START)
            {
                Serial.printf("Update: %s\n", upload.filename.c_str());
                if (!Update.begin(UPDATE_SIZE_UNKNOWN))
                { //start with max available size
                    Update.printError(Serial);
                }
            }
            else if (upload.status == UPLOAD_FILE_WRITE)
            {
                if (Update.write(upload.buf, upload.currentSize) != upload.currentSize)
                {
                    Update.printError(Serial);
                }
            }
            else if (upload.status == UPLOAD_FILE_END)
            {
                if (Update.end(true))
                { //true to set the size to the current progress
                    Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
                }
                else
                {
                    Update.printError(Serial);
                }
            } });
>>>>>>> 04c89170e6d9fe92b9779a399efd53a15a70db11
}
