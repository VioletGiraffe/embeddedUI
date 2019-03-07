#pragma once

#include <Adafruit_GFX.h>

#ifndef ST7735_BLACK // Adafruit headers lack an include guard
#include <Adafruit_ST7735.h>
#endif

#define TFT_CS 7
#define TFT_RST 9 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC 8
Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);

inline void tftInit() {
    tft.initR(INITR_MINI160x80);
}