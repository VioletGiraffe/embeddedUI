#include "Screen.h"

#if defined ARDUINO_AVR_UNO

	#include "TFTLCD_Screen_Setup.h"
	#include "Painter_Adafruit_TFTLCD.hpp"
	using PainterImplementation = PainterAdafruitTftLcd;

#elif defined ARDUINO_SAM_DUE

	#include "Mcufriend_Screen_Setup.h"
	#include "Painter_MCUFRIEND.h"
	using PainterImplementation = PainterMcufriend;

#elif defined ESP32

	#include "ST7735_Screen_Setup_Adafruit.h"
	#include "Painter_Adafruit_ST7735.h"
	using PainterImplementation = PainterAdafruitST7735;

#endif

#include "Mandelbrot.hpp"

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
