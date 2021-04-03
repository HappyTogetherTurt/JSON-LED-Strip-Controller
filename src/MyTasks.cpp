#include <Arduino.h>
#include <EEPROM.h>

#include "MyTasks.h"
#include "MyLeds.h"

TaskHandle_t LED;

void startLedTask()
{
    xTaskCreatePinnedToCore(
        ledHandling,        // Function that should be called
        "LED Handling", // Name of the task (for debugging)
        5000,           // Stack size (bytes)
        NULL,           // Parameter to pass
        1,              // Task priority
        &LED,           // Task Handle
        1               //Core
    );
}

void restartIntoMode(int mode)
{
  EEPROM.write(0, mode);
  EEPROM.commit();
  ESP.restart();
}