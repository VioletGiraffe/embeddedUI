#include "Screen.h"

#if defined ARDUINO_AVR_UNO

	// #include "SSD1351_Screen_Setup_Adafruit.h"
	// #include "Painter_Adafruit_SSD1351.h"
	// using PainterImplementation = PainterAdafruitSsd1351;

	#include "ST7735S_IPS_Screen_Setup_Adafruit.h"
	#include "Painter_Adafruit_ST7735.h"
	using PainterImplementation = PainterAdafruitST7735;

#elif defined ARDUINO_SAM_DUE

	#include "Mcufriend_Screen_Setup.h"
	#include "Painter_MCUFRIEND.h"
	using PainterImplementation = PainterMcufriend;

#elif defined ESP32

	#include "ST7735_Screen_Setup_Adafruit.h"
	#include "Painter_Adafruit_ST7735.h"
	using PainterImplementation = PainterAdafruitST7735;

#endif

struct Initializer {
	inline Initializer() {
		// Has to be set prior to creating the Screen object
		PainterImplementation::setDisplayInstance(tft);
	}
} staticInitializer;

#include "Colors_test.hpp"

void setup(void)
{
	Serial.begin(115200);
	Serial.println(F("Bootup successful"));

	setupExample();
}

void loop()
{
	loopExample();
}
