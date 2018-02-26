#pragma once

template <class ConcretePainter>
class TestScreen: public Screen<ConcretePainter, TestScreen<ConcretePainter>> {

	template <typename U>
	friend class Widget;

public:
	TestScreen() {
	}

	void setDisablePaint(bool disable) {
		_disablePaint = disable;
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

		if (!_disablePaint)
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

				if (!isInside)
				{
					const float t = (float)n * maxIterationsInverse;
  
					// Use smooth polynomials for r, g, b
					const int r = (int)(9*(1-t)*t*t*t*255.0f);
					const int g = (int)(15*(1-t)*(1-t)*t*t*255.0f);
					const int b =  (int)(8.5*(1-t)*(1-t)*(1-t)*t*255.0f);

					if (!_disablePaint)
						painter.setPixel(x, y, Color(r, g, b));
				}
			}
		}
	}

private:
	bool _disablePaint = false;
};

TestScreen<PainterImplementation> screen;

inline void setupExample()
{
	tftInit();

	auto start = millis();
	screen.update();
	const auto totalTime = millis() - start;

	screen.setDisablePaint(true);

	start = millis();
	screen.update();
	const auto calculationTime = millis() - start;
	const auto paintTime = totalTime - calculationTime;

	Serial.println("Drawing Mandelbrot set in " + String(screen.width()) + '*' + String(screen.height()));
	Serial.println("Total time: " + String(totalTime) + " ms (" + String((uint32_t)screen.width() * (uint32_t)screen.height() * 1000 / totalTime) + " pixels / second)");
	Serial.println("Calculation time: " + String(calculationTime) + " ms (" + String((uint32_t)screen.width() * (uint32_t)screen.height() * 1000 / calculationTime) + " pixels / second)");
	Serial.println("Paint time: " + String(paintTime) + " ms (" + String((uint32_t)screen.width() * (uint32_t)screen.height() * 1000 / paintTime) + " pixels / second)");
}

inline void loopExample()
{
	
}