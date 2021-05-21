#ifndef MYLEDS
#define MYLEDS

#include <FastLED.h>

#define NUM_LEDS 300
#define DATA_PIN 4

void ledSetup();
void blink(int blinkdelay);
void fill();
void ledHandling(void *parameter);

extern int data[10];
extern CRGB leds[NUM_LEDS];

enum Mode
{

UPDATE,
MANUAL,
BREATHE,
RAINBOW_CHASER,
FLOW,
CHRISTMAS

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
    BREATHE_SPEED
};

enum RainbowChaserEnum
{
    RAINBOW_CHASER_SPEED
};

enum FlowEnum
{
    FLOW_SPEED
};

enum ChristmasEnum
{
    CHRISTMAS_SPEED
};

#endif