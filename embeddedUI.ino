#include "Painter_Adafruit_SSD1351.h"
#include "Screen.h"

constexpr auto dc = 4;
constexpr auto cs = 5;
constexpr auto rst = 6;
Adafruit_SSD1351 tft = Adafruit_SSD1351(cs, dc, rst);

using PainterImplementation = PainterAdafruitSsd1351;

template <class ConcretePainter>
class TestScreen: public Screen<ConcretePainter> {
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

	void onDraw(Size /* regionToUpdate */) {
		

		float MinRe = -2.0;
		float MaxRe = 1.0;
		float MinIm = -1.2;
		float MaxIm = MinIm+(MaxRe-MinRe)*screenHeight()/screenWidth();
		float Re_factor = (MaxRe-MinRe)/(screenWidth()-1);
		float Im_factor = (MaxIm-MinIm)/(screenHeight()-1);
		constexpr unsigned int MaxIterations = 30;

		ConcretePainter painter;
		painter.fillScreen(Color::white());

		for(unsigned int y = 0, height = screenHeight(); y < height; ++y)
		{
			float c_im = MaxIm - y*Im_factor;
			for(unsigned int x = 0, width = screenWidth(); x < width; ++x)
			{
				float c_re = MinRe + x*Re_factor;

				float Z_re = c_re, Z_im = c_im;
				bool isInside = true;
				for(unsigned int n = 0; n < MaxIterations; ++n)
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
					painter.setPixel(x, y, Color::black());
			}
		}
	}
};

TestScreen<PainterImplementation> screen;

void setup(void)
{
	PainterImplementation::setDisplayInstance(tft);
	tft.begin();
}

void loop()
{
	screen.update();
}
