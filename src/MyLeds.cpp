#include <FastLED.h>

#include <Preferences.h>

#include "MyLeds.h"

CRGB leds[NUM_LEDS];
int data[11];
Mode modeVar;
Preferences preferences;

void ledSetup()
{
    modeVar = (Mode)preferences.getInt("mode");
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

    data[RED] = preferences.getInt("red");
    data[GREEN] = preferences.getInt("green");
    data[BLUE] = preferences.getInt("blue");

    data[BREATHE_DELAY] = 5;

    data[CHASER_DELAY] = 80;

    data[FLOW_DELAY] = 20;

    data[EMBER_DELAY] = 1;

    data[NOTIFY_RED] = preferences.getInt("notify_red");
    data[NOTIFY_GREEN] = preferences.getInt("notify_green");
    data[NOTIFY_BLUE] = preferences.getInt("notify_blue");
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
            blink(500);
        }

    case MANUAL:
        for (;;)
        {
            for (;;)
            {
                for (int i = 0; i <= NUM_LEDS - 1; i++)
                {
                    leds[i].setRGB(data[RED], data[GREEN], data[BLUE]);
                    FastLED.show();
                    vTaskDelay(1);
                }
            }
        }
        break;

    case BREATHE:
        for (int i = 0; i <= NUM_LEDS - 1; i++)
        {
            leds[i].setRGB(data[RED], data[GREEN], data[BLUE]);
        }
        FastLED.show();
        for (;;)
        {
            for (int i = 0; i <= 150; i++)
            {
                for (int j = 0; j <= NUM_LEDS - 1; j++)
                {
                    leds[j].setRGB(data[RED], data[GREEN], data[BLUE]);
                }
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(data[BREATHE_DELAY]);
            }
            for (int i = 150; i <= 255; i++)
            {
                for (int j = 0; j <= NUM_LEDS - 1; j++)
                {
                    leds[j].setRGB(data[RED], data[GREEN], data[BLUE]);
                }
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(data[BREATHE_DELAY] / 2);
            }
            for (int i = 255; i >= 150; i--)
            {
                for (int j = 0; j <= NUM_LEDS - 1; j++)
                {
                    leds[j].setRGB(data[RED], data[GREEN], data[BLUE]);
                }
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(data[BREATHE_DELAY] / 2);
            }
            for (int i = 150; i >= 0; i--)
            {
                for (int j = 0; j <= NUM_LEDS - 1; j++)
                {
                    leds[j].setRGB(data[RED], data[GREEN], data[BLUE]);
                }
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(data[BREATHE_DELAY]);
            }
        }
        break;

    case CHASER:
        for (;;)
        {
            for (int i = 0; i <= NUM_LEDS - 1; i++)
            {
                leds[i - 1] = CRGB::Black;
                leds[i].setRGB(data[RED], data[GREEN], data[BLUE]);
                FastLED.show();
                vTaskDelay(data[CHASER_DELAY]);
            }
            for (int i = NUM_LEDS - 1; i >= 0; i--)
            {
                leds[i + 1] = CRGB::Black;
                leds[i].setRGB(data[RED], data[GREEN], data[BLUE]);
                FastLED.show();
                vTaskDelay(data[CHASER_DELAY]);
            }
        }
        break;

    case FLOW:
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
                leds[emberLit].setRGB(data[RED], data[GREEN], data[BLUE]);
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(data[EMBER_DELAY] * 2);
            }
            for (int i = 128; i <= 255; i++)
            {
                leds[emberLit].setRGB(data[RED], data[GREEN], data[BLUE]);
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(data[EMBER_DELAY]);
            }
            for (int i = 255; i >= 128; i--)
            {
                leds[emberLit].setRGB(data[RED], data[GREEN], data[BLUE]);
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(data[EMBER_DELAY]);
            }
            for (int i = 128; i >= 0; i--)
            {
                leds[emberLit].setRGB(data[RED], data[GREEN], data[BLUE]);
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(data[EMBER_DELAY] * 2);
            }
            leds[emberLit].setRGB(0, 0, 0);
        }
        break;

    case NOTIFY:
        struct Colour
        {
            int red;
            int green;
            int blue;
        };
        Colour colour;

        data[NOTIFY_NOTIFICATION] = 0;

        for (int i = 0; i <= NUM_LEDS - 1; i++)
        {
            leds[i].setRGB(0, 0, 0);
            FastLED.show();
        }

        for (;;)
        {
            while (data[NOTIFY_NOTIFICATION] == 0 || data[NOTIFY_NOTIFICATION] == 2)
            {
                vTaskDelay(1);
            }
            colour.red = data[NOTIFY_RED];
            colour.green = data[NOTIFY_GREEN];
            colour.blue = data[NOTIFY_BLUE];
            for (int i = 0; i <= 150; i++)
            {
                for (int j = 0; j <= NUM_LEDS - 1; j++)
                {
                    if (data[NOTIFY_NOTIFICATION] == 0)
                    {
                        break;
                    }
                    leds[j].setRGB(colour.red, colour.green, colour.blue);
                }
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(10);
            }
            for (int i = 150; i <= 255; i++)
            {
                for (int j = 0; j <= NUM_LEDS - 1; j++)
                {
                    if (data[NOTIFY_NOTIFICATION] == 0)
                    {
                        break;
                    }
                    leds[j].setRGB(colour.red, colour.green, colour.blue);
                }
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(5);
            }
            for (int i = 255; i >= 150; i--)
            {
                for (int j = 0; j <= NUM_LEDS - 1; j++)
                {
                    if (data[NOTIFY_NOTIFICATION] == 0)
                    {
                        break;
                    }
                    leds[j].setRGB(colour.red, colour.green, colour.blue);
                }
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(5);
            }
            for (int i = 150; i >= 0; i--)
            {
                for (int j = 0; j <= NUM_LEDS - 1; j++)
                {
                    if (data[NOTIFY_NOTIFICATION] == 0)
                    {
                        break;
                    }
                    leds[j].setRGB(colour.red, colour.green, colour.blue);
                }
                FastLED.setBrightness(i);
                FastLED.show();
                vTaskDelay(10);
            }
        }

    default:
        for (;;)
        {
            blink(50);
        }
        break;
    }
}