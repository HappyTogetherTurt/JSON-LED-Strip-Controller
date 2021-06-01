#include <FastLED.h>

#include <Preferences.h>

#include "MyLeds.h"

CRGB leds[NUM_LEDS];
int data[10];
Mode modeVar;
Preferences preferences;

void ledSetup()
{
    modeVar = (Mode) preferences.getInt("mode");
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
    for (int i = 0; i <= NUM_LEDS - 1; i++)
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

    switch (preferences.getInt("mode"))
    {

    case UPDATE:
        for (;;)
        {
            blink(50);
        }

    case MANUAL:
        data[MANUAL_RED] = preferences.getInt("red");
        data[MANUAL_GREEN] = preferences.getInt("green");
        data[MANUAL_BLUE] = preferences.getInt("blue");
        for (;;)
        {
            for (;;)
            {
                for (int i = 0; i <= NUM_LEDS - 1; i++)
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
        data[MANUAL_RED] = preferences.getInt("red");
        data[MANUAL_GREEN] = preferences.getInt("green");
        data[MANUAL_BLUE] = preferences.getInt("blue");
        data[BREATHE_DELAY] = 5;
        for (int i = 0; i <= NUM_LEDS - 1; i++)
        {
            leds[i].setRGB(data[BREATHE_RED], data[BREATHE_GREEN], data[BREATHE_BLUE]);
        }
        FastLED.show();
        for (;;)
        {
            for (int i = 0; i <= 150; i++)
            {
                for (int j = 0; j <= NUM_LEDS - 1; j++)
                {
                    leds[j].setRGB(data[BREATHE_RED], data[BREATHE_GREEN], data[BREATHE_BLUE]);
                }
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(data[BREATHE_DELAY]);
            }
            for (int i = 150; i <= 255; i++)
            {
                for (int j = 0; j <= NUM_LEDS - 1; j++)
                {
                    leds[j].setRGB(data[BREATHE_RED], data[BREATHE_GREEN], data[BREATHE_BLUE]);
                }
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(data[BREATHE_DELAY] / 2);
            }
            for (int i = 255; i >= 150; i--)
            {
                for (int j = 0; j <= NUM_LEDS - 1; j++)
                {
                    leds[j].setRGB(data[BREATHE_RED], data[BREATHE_GREEN], data[BREATHE_BLUE]);
                }
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(data[BREATHE_DELAY] / 2);
            }
            for (int i = 150; i >= 0; i--)
            {
                for (int j = 0; j <= NUM_LEDS - 1; j++)
                {
                    leds[j].setRGB(data[BREATHE_RED], data[BREATHE_GREEN], data[BREATHE_BLUE]);
                }
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(data[BREATHE_DELAY]);
            }
        }
        break;

    case CHASER:
        data[MANUAL_RED] = preferences.getInt("red");
        data[MANUAL_GREEN] = preferences.getInt("green");
        data[MANUAL_BLUE] = preferences.getInt("blue");
        data[CHASER_DELAY] = 80;
        for (;;)
        {
            for (int i = 0; i <= NUM_LEDS - 1; i++)
            {
                leds[i - 1] = CRGB::Black;
                leds[i].setRGB(data[MANUAL_RED], data[MANUAL_GREEN], data[MANUAL_BLUE]);
                FastLED.show();
                vTaskDelay(data[CHASER_DELAY]);
            }
            for (int i = NUM_LEDS - 1; i >= 0; i--)
            {
                leds[i + 1] = CRGB::Black;
                leds[i].setRGB(data[MANUAL_RED], data[MANUAL_GREEN], data[MANUAL_BLUE]);
                FastLED.show();
                vTaskDelay(data[CHASER_DELAY]);
            }
        }
        break;

    case FLOW:
        data[FLOW_DELAY] = 20;
        for (;;)
        {
            for (int i = 0; i <= 255; i++)
            {
                for (int j = 0; j <= NUM_LEDS - 1; j++)
                {
                    leds[j].setHue(i);
                }
                FastLED.show();
                vTaskDelay(data[FLOW_DELAY]);
            }
        }
        break;

    case EMBER:
        int emberLit;
        data[MANUAL_RED] = preferences.getInt("red");
        data[MANUAL_GREEN] = preferences.getInt("green");
        data[MANUAL_BLUE] = preferences.getInt("blue");
        data[EMBER_DELAY] = 1;
        for (int i = 0; i <= NUM_LEDS - 1; i++)
        {
            leds[i].setRGB(0, 0, 0);
        }
        for (;;)
        {
            int lastEmberLit = emberLit;
            while (emberLit == lastEmberLit)
            {
                emberLit = random(NUM_LEDS);
            }

            for (int i = 0; i <= 128; i++)
            {
                leds[emberLit].setRGB(data[MANUAL_RED], data[MANUAL_GREEN], data[MANUAL_BLUE]);
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(data[EMBER_DELAY] * 2);
            }
            for (int i = 128; i <= 255; i++)
            {
                leds[emberLit].setRGB(data[MANUAL_RED], data[MANUAL_GREEN], data[MANUAL_BLUE]);
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(data[EMBER_DELAY]);
            }
            for (int i = 255; i >= 128; i--)
            {
                leds[emberLit].setRGB(data[MANUAL_RED], data[MANUAL_GREEN], data[MANUAL_BLUE]);
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(data[EMBER_DELAY]);
            }
            for (int i = 128; i >= 0; i--)
            {
                leds[emberLit].setRGB(data[MANUAL_RED], data[MANUAL_GREEN], data[MANUAL_BLUE]);
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(data[EMBER_DELAY] * 2);
            }
            leds[emberLit].setRGB(0, 0, 0);
        }

    default:
        for (;;)
        {
            blink(50);
        }
        break;
    }
}