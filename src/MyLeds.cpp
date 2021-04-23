#include <FastLED.h>
#include <EEPROM.h>

#include "MyLeds.h"

CRGB leds[NUM_LEDS];
int data[10];
Mode modeVar;

void ledSetup()
{
<<<<<<< HEAD
=======
    modeVar = (Mode)EEPROM.read(MODE_ADDRESS);
>>>>>>> 04c89170e6d9fe92b9779a399efd53a15a70db11
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void blink(int blinkDelay)
{
    digitalWrite(2, HIGH);
    delay(blinkDelay);
    digitalWrite(2, LOW);
    delay(blinkDelay);
}

void fill(int r, int g, int b, bool show)
{
    for (int i = 0; i <= 299; i++)
    {
        leds[i].setRGB(r, g, b);
    }
    if (show)
    {
        FastLED.show();
    }
}

void ledHandling(void *parameter)
{
    for (int i = 0; i <= NUM_LEDS; i++)
    {
        leds[i].setRGB(0, 0, 0);
    }

    switch (EEPROM.read(MODE_ADDRESS))
    {

<<<<<<< HEAD
    case UPDATE:
        for (int i = 0; i <= 299; i++)
        {
            leds[i].setRGB(0, 0, 255);
        }
        FastLED.show();
        for (;;)
        {
            blink(200);
=======
    case MANUAL:
        for (;;)
        {
            for (int i = 0; i <= 299; i++)
            {
                leds[i].setRGB(data[MANUAL_RED], data[MANUAL_RED], data[MANUAL_BLUE]);
                vTaskDelay(1);
            }
>>>>>>> 04c89170e6d9fe92b9779a399efd53a15a70db11
        }

<<<<<<< HEAD
    case MANUAL:
        data[MANUAL_RED] = 0;
        data[MANUAL_GREEN] = 0;
        data[MANUAL_BLUE] = 0;
        for (;;)
        {
            for (int i = 0; i <= 299; i++)
            {
                leds[i].setRGB(data[MANUAL_RED], data[MANUAL_GREEN], data[MANUAL_BLUE]);
                FastLED.show();
                vTaskDelay(1);
            }
        }
        break;

=======
>>>>>>> 04c89170e6d9fe92b9779a399efd53a15a70db11
    case BREATHE:
        for (int i = 0; i <= 299; i++)
        {
            leds[i].setRGB(EEPROM.read(RED_ADDRESS), EEPROM.read(GREEN_ADDRESS), EEPROM.read(BLUE_ADDRESS));
        }
        FastLED.show();
        for (;;)
        {
            for (int i = 0; i <= 128; i++)
            {
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(5 / portTICK_PERIOD_MS);
            }
            for (int i = 128; i <= 255; i++)
            {
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(1 / portTICK_PERIOD_MS);
            }
            for (int i = 255; i >= 128; i--)
            {
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(1 / portTICK_PERIOD_MS);
            }
            for (int i = 128; i >= 0; i--)
            {
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(5 / portTICK_PERIOD_MS);
            }
        }
        break;

    case RAINBOW_CHASER:
        for (;;)
        {
            for (int i = 0; i <= 299; i++)
            {
                leds[i - 1] = CRGB::Black;
                leds[i].setHue(i);
                FastLED.show();
<<<<<<< HEAD
                vTaskDelay(data[RAINBOW_CHASER_SPEED]);
=======
                vTaskDelay(data[RAINBOW_CHASER_DELAY]);
>>>>>>> 04c89170e6d9fe92b9779a399efd53a15a70db11
            }
            for (int i = 299; i >= 0; i--)
            {
                leds[i + 1] = CRGB::Black;
                leds[i].setHue(i);
                FastLED.show();
<<<<<<< HEAD
                vTaskDelay(data[RAINBOW_CHASER_SPEED]);
=======
                vTaskDelay(data[RAINBOW_CHASER_DELAY]);
>>>>>>> 04c89170e6d9fe92b9779a399efd53a15a70db11
            }
        }
        break;

    case FLOW:
        for (;;)
        {
            for (int i = 0; i <= 255; i++)
            {
                for (int j = 0; j <= 299; j++)
                {
                    leds[j].setHue(i);
                }
                FastLED.show();
                vTaskDelay(data[FLOW_SPEED]);
            }
        }
        break;

    case CHRISTMAS:

        for (;;)
        {
            for (int i = 0; i <= 299; i++)
            {
                if (i % 2 == 0)
                {
                    leds[i].setRGB(0, 255, 0);
                }
                else
                {
                    leds[i].setRGB(255, 0, 0);
                }
            }
            FastLED.show();
            vTaskDelay(data[CHRISTMAS_SPEED]);

            for (int i = 0; i <= 299; i++)
            {
                if (i % 2 == 1)
                {
                    leds[i].setRGB(0, 255, 0);
                }
                else
                {
                    leds[i].setRGB(255, 0, 0);
                }
            }
            FastLED.show();
            vTaskDelay(data[CHRISTMAS_SPEED]);
        }

        break;

    default:
        for (;;)
        {
            blink(50);
        }
        break;
    }
}