#include "Screen.h"

#if defined ARDUINO_AVR_UNO

	#include "TFTLCD_Screen_Setup.h"
	#include "Painter_Adafruit_TFTLCD.hpp"
	using PainterImplementation = PainterAdafruitTftLcd;

#elif defined ARDUINO_SAM_DUE

	#include "SSD1351_Screen_Setup_Adafruit.h"
	#include "Painter_Adafruit_SSD1351.h"
	using PainterImplementation = PainterAdafruitSsd1351;

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

template <class ConcretePainter>
class TestScreen: public Screen<ConcretePainter, TestScreen<ConcretePainter>> {

	template <typename U>
	friend class Widget;

public:
	TestScreen() {
	}

protected:
	bool pointBelongsToCardioid(float re, float im)
	{
		const auto x_offset = re - 0.25f;
		const auto im_sqr = im * im;

		const auto q = x_offset * x_offset + im_sqr;
		return q * (q + x_offset) < 0.25f * im_sqr;
	}

	void onDraw(Size /* regionToUpdate */)
	{
		float MinRe = -2.0;
		float MaxRe = 1.0;
		float MinIm = -1.2;

		ConcretePainter painter;
		const auto w = painter.screenWidth(), h = painter.screenHeight();

		float MaxIm = MinIm+(MaxRe-MinRe)*h/w;
		float Re_factor = (MaxRe-MinRe)/(w-1);
		float Im_factor = (MaxIm-MinIm)/(h-1);
		constexpr unsigned int MaxIterations = 30;
		constexpr float maxIterationsInverse = 1.0f / MaxIterations;

		painter.fillScreen(Color::black());

		for(unsigned int y = 0; y < h; ++y)
		{
			float c_im = MaxIm - y*Im_factor;
			
			for(unsigned int x = 0; x < w; ++x)
			{
				float c_re = MinRe + x*Re_factor;

				float Z_re = c_re, Z_im = c_im;
				bool isInside = true;
				unsigned int n = 0;
				for(; n < MaxIterations; ++n)
				{
					float Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
					if(Z_re2 + Z_im2 > 4)
					{
						isInside = false;
						break;
					}
					Z_im = 2*Z_re*Z_im + c_im;
					Z_re = Z_re2 - Z_im2 + c_re;
				}

				if (isInside)
				{
					const float t = (float)n * maxIterationsInverse;
  
					// Use smooth polynomials for r, g, b
					const int r = (int)(9*(1-t)*t*t*t*255);
					const int g = (int)(15*(1-t)*(1-t)*t*t*255);
					const int b =  (int)(8.5*(1-t)*(1-t)*(1-t)*t*255);	
					painter.setPixel(x, y, Color(200, 200, 200));
				}
			}
		}
	}
};

TestScreen<PainterImplementation> screen;

void setup(void)
{
	Serial.begin(115200);
	Serial.println(F("Bootup successful"));

	tftInit();

	PainterAdafruitSsd1351().fillScreen(Color().to565());
}

uint32_t loopCount = 0;

void loop()
{
	Serial.println(++loopCount);
	
	//screen.update();
}
