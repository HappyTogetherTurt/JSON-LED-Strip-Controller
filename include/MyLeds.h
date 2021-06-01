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

extern int data[10];
extern Preferences preferences;

enum Mode
{
    UPDATE,
    MANUAL,
    BREATHE,
    CHASER,
    FLOW,
    EMBER
};

extern Mode modeVar;

enum Address
{
    MODE_ADDRESS,
    RED_ADDRESS,
    GREEN_ADDRESS,
    BLUE_ADDRESS
};

//Mode-specific enums

enum ManualEnum
{
    MANUAL_RED,
    MANUAL_GREEN,
    MANUAL_BLUE,
    MANUAL_BREATHE
};

enum BreatheEnum
{
    BREATHE_RED,
    BREATHE_GREEN,
    BREATHE_BLUE,
    BREATHE_DELAY
};

enum ChaserEnum
{
    CHASER_DELAY = 3
};

enum FlowEnum
{
    FLOW_DELAY
};

enum EmberEnum
{
    EMBER_DELAY = 3
};

#endif