#pragma once

#include <MCUFRIEND_kbv.h>

constexpr auto dc = 4;
constexpr auto cs = 5;
constexpr auto rst = 6;

MCUFRIEND_kbv tft;

inline void tftInit() {
    tft.begin(tft.readID());
    tft.setRotation(3);
}