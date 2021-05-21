#include <FastLED.h>
#include <EEPROM.h>

#include "MyLeds.h"

CRGB leds[NUM_LEDS];
int data[10];
Mode modeVar;

void ledSetup()
{
    modeVar = (Mode)EEPROM.read(MODE_ADDRESS);
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

    case MANUAL:
        data[MANUAL_RED] = EEPROM.read(RED_ADDRESS);
        data[MANUAL_GREEN] = EEPROM.read(GREEN_ADDRESS);
        data[MANUAL_BLUE] = EEPROM.read(BLUE_ADDRESS);
        for (;;)
        {
            for (;;)
            {
                for (int i = 0; i <= 299; i++)
                {
                    if (data[MANUAL_BREATHE])
                    {
                        break;
                    }
                    leds[i].setRGB(data[MANUAL_RED], data[MANUAL_GREEN], data[MANUAL_BLUE]);
                    FastLED.show();
                    vTaskDelay(1);
                }
                if (data[MANUAL_BREATHE])
                {
                    break;
                }
            }
            /*---*/
            for (;;)
            {
                for (int i = 0; i <= 128; i++)
                {
                    if (!data[MANUAL_BREATHE])
                    {
                        break;
                    }
                    leds[i].setRGB(data[BREATHE_RED], data[BREATHE_GREEN], data[BREATHE_BLUE]);
                    FastLED.setBrightness(i);
                    FastLED.show();
                    vTaskDelay(5 / portTICK_PERIOD_MS);
                }
                for (int i = 128; i <= 255; i++)
                {
                    if (!data[MANUAL_BREATHE])
                    {
                        break;
                    }
                    leds[i].setRGB(data[BREATHE_RED], data[BREATHE_GREEN], data[BREATHE_BLUE]);
                    FastLED.setBrightness(i);
                    FastLED.show();
                    vTaskDelay(1 / portTICK_PERIOD_MS);
                }
                for (int i = 255; i >= 128; i--)
                {
                    if (!data[MANUAL_BREATHE])
                    {
                        break;
                    }
                    leds[i].setRGB(data[BREATHE_RED], data[BREATHE_GREEN], data[BREATHE_BLUE]);
                    FastLED.setBrightness(i);
                    FastLED.show();
                    vTaskDelay(1 / portTICK_PERIOD_MS);
                }
                for (int i = 128; i >= 0; i--)
                {
                    if (!data[MANUAL_BREATHE])
                    {
                        break;
                    }
                    leds[i].setRGB(data[BREATHE_RED], data[BREATHE_GREEN], data[BREATHE_BLUE]);
                    FastLED.setBrightness(i);
                    FastLED.show();
                    vTaskDelay(5 / portTICK_PERIOD_MS);
                }
                if (!data[MANUAL_BREATHE])
                {
                    FastLED.setBrightness(255);
                    break;
                }
            }
        }
        break;

    case BREATHE:
        data[BREATHE_RED] = EEPROM.read(RED_ADDRESS);
        data[BREATHE_GREEN] = EEPROM.read(GREEN_ADDRESS);
        data[BREATHE_BLUE] = EEPROM.read(BLUE_ADDRESS);
        for (int i = 0; i <= 299; i++)
        {
            leds[i].setRGB(data[BREATHE_RED], data[BREATHE_GREEN], data[BREATHE_BLUE]);
        }
        FastLED.show();
        for (;;)
        {
            for (int i = 0; i <= 128; i++)
            {
                leds[i].setRGB(data[BREATHE_RED], data[BREATHE_GREEN], data[BREATHE_BLUE]);
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(5 / portTICK_PERIOD_MS);
            }
            for (int i = 128; i <= 255; i++)
            {
                leds[i].setRGB(data[BREATHE_RED], data[BREATHE_GREEN], data[BREATHE_BLUE]);
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(1 / portTICK_PERIOD_MS);
            }
            for (int i = 255; i >= 128; i--)
            {
                leds[i].setRGB(data[BREATHE_RED], data[BREATHE_GREEN], data[BREATHE_BLUE]);
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(1 / portTICK_PERIOD_MS);
            }
            for (int i = 128; i >= 0; i--)
            {
                leds[i].setRGB(data[BREATHE_RED], data[BREATHE_GREEN], data[BREATHE_BLUE]);
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(5 / portTICK_PERIOD_MS);
            }
        }
        break;

    case RAINBOW_CHASER:
        data[RAINBOW_CHASER_DELAY] = 4;
        for (;;)
        {
            for (int i = 0; i <= 299; i++)
            {
                leds[i - 1] = CRGB::Black;
                leds[i].setHue(i);
                FastLED.show();
                vTaskDelay(data[RAINBOW_CHASER_DELAY]);
            }
            for (int i = 299; i >= 0; i--)
            {
                leds[i + 1] = CRGB::Black;
                leds[i].setHue(i);
                FastLED.show();
                vTaskDelay(data[RAINBOW_CHASER_DELAY]);
            }
        }
        break;

    case FLOW:
        data[FLOW_DELAY] = 20;
        for (;;)
        {
            for (int i = 0; i <= 255; i++)
            {
                for (int j = 0; j <= 299; j++)
                {
                    leds[j].setHue(i);
                }
                FastLED.show();
                vTaskDelay(data[FLOW_DELAY]);
            }
        }
        break;

    case CHRISTMAS:
        data[CHRISTMAS_DELAY] = 140;
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
            vTaskDelay(data[CHRISTMAS_DELAY]);

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
            vTaskDelay(data[CHRISTMAS_DELAY]);
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