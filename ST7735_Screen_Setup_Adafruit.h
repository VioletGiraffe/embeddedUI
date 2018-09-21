#pragma once

#include <Adafruit_GFX.h>

#ifndef ST7735_BLACK // Adafruit headers lack an include guard
#include <Adafruit_ST7735.h>
#endif

#define TFT_CS 10
#define TFT_DC 8
#define TFT_RST 0  // you can also connect this to the Arduino reset, in which case, set this #define pin to 0!
Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);

inline void tftInit() {
    tft.initR(INITR_144GREENTAB);
}