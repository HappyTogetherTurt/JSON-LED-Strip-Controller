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

<<<<<<< HEAD
enum Mode
=======
enum Mode 
>>>>>>> 04c89170e6d9fe92b9779a399efd53a15a70db11
{
    UPDATE,
    MANUAL,
    RAINBOW_CHASER,
    BREATHE,
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
    MANUAL_BLUE
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