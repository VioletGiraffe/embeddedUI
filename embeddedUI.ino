#include "Screen.h"
#include "Painter_SSD13XX.h"

// constexpr auto dc = 4;
// constexpr auto cs = 5;
// constexpr auto rst = 6;
// Adafruit_SSD1351 tft = Adafruit_SSD1351(cs, dc, rst);

#define _cs   17  // goes to TFT CS
#define _dc   16  // goes to TFT DC
#define _mosi 23  // goes to TFT MOSI
#define _sclk 18  // goes to TFT SCK/CLK
#define _rst  5   // ESP RST to TFT RESET
#define _miso     // Not connected
//       3.3V     // Goes to TFT LED  
//       5v       // Goes to TFT Vcc
//       Gnd      // Goes to TFT Gnd      

SSD_13XX tft(_cs, _dc);
using PainterImplementation = PainterSsd13XX;

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

	void onDraw(Size /* regionToUpdate */) {
		

		float MinRe = -2.0;
		float MaxRe = 1.0;
		float MinIm = -1.2;
		float MaxIm = MinIm+(MaxRe-MinRe)*this->_size.height()/this->_size.width();
		float Re_factor = (MaxRe-MinRe)/(this->_size.width()-1);
		float Im_factor = (MaxIm-MinIm)/(this->_size.height()-1);
		constexpr unsigned int MaxIterations = 30;

		ConcretePainter painter;
		painter.fillScreen(Color::violet());

		for(unsigned int y = 0, height = this->_size.height(); y < height; ++y)
		{
			float c_im = MaxIm - y*Im_factor;
			for(unsigned int x = 0, width = this->_size.width(); x < width; ++x)
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
					painter.setPixel(Point{x, y}, Color::black());
			}
		}
	}
};

TestScreen<PainterImplementation> screen;

void setup(void)
{
	Serial.begin(115200);
	Serial.println(F("Bootup successful"));

	tft.begin();
	PainterImplementation().fillScreen(Color::red());
}

uint32_t loopCount = 0;

void loop()
{
	Serial.println(++loopCount);
	
	screen.update();
}
