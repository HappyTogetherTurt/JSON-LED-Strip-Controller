#ifndef MYLEDS
#define MYLEDS

#include <FastLED.h>
#include <Preferences.h>

#define NUM_LEDS 8
#define DATA_PIN 4

void ledSetup();
void blink();
void fill();
void ledHandling(void *parameter);

extern int data[11];
extern Preferences preferences;

enum Mode
{
    UPDATE,
    MANUAL,
    BREATHE,
    CHASER,
    FLOW,
    EMBER,
    NOTIFY
};

extern Mode modeVar;

enum Address
{
    MODE_ADDRESS,
    RED_ADDRESS,
    GREEN_ADDRESS,
    BLUE_ADDRESS
};

// Mode-specific enums

enum ManualEnum
{
    RED,
    GREEN,
    BLUE
};

enum BreatheEnum
{
    BREATHE_DELAY = 3
};

enum ChaserEnum
{
    CHASER_DELAY = 4
};

enum FlowEnum
{
    FLOW_DELAY = 5
};

enum EmberEnum
{
    EMBER_DELAY = 6
};

enum NotifyEnum
{
    NOTIFY_RED = 7,
    NOTIFY_GREEN = 8,
    NOTIFY_BLUE = 9,
    NOTIFY_NOTIFICATION = 10
};

#endif
