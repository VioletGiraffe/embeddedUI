#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>

#include "Painter_Adafruit_SSD1351.h"

constexpr auto dc = 4;
constexpr auto cs = 5;
constexpr auto rst = 6;
Adafruit_SSD1351 tft = Adafruit_SSD1351(cs, dc, rst);
PainterAdafruitSsd1351<tft> painter;

void setup(void) {
 
	tft.begin();

	painter.fillScreen(Color(255, 127, 0));
}

void loop()
{
}