#pragma once

#include <Adafruit_SSD1351.h>

constexpr auto dc = 4;
constexpr auto cs = 5;
constexpr auto rst = 6;

Adafruit_SSD1351 tft = Adafruit_SSD1351(cs, dc, rst);

inline void tftInit() {
    tft.begin();
}