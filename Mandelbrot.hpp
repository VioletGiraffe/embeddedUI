#pragma once

#include "UiHierarchy.hpp"

#include <complex>

DEFINE_SCREEN(TestScreen) {

	template <typename U>
	friend class Widget;

	void setDisablePaint(bool disable) {
		_disablePaint = disable;
	}

protected:
	inline bool pointBelongsToCardioid(const std::complex<float> point)
	{
		const auto x_offset = point.real() - 0.25f;
		const auto im_sqr = point.imag() * point.imag();

		const auto q = x_offset * x_offset + im_sqr;
		return q * (q + x_offset) < 0.25f * im_sqr;
	}


	void onDraw(Size /* regionToUpdate */)
	{
		ConcretePainter painter;
		const auto w = painter.screenWidth(), h = painter.screenHeight();

		constexpr float MinRe = -2.0;
		constexpr float MaxRe = 1.0;
		constexpr float MinIm = -1.2;
		const float MaxIm = MinIm+(MaxRe-MinRe)*h/w;
		const float Re_factor = (MaxRe-MinRe)/(w-1);
		const float Im_factor = (MaxIm-MinIm)/(h-1);
		constexpr uint8_t MaxIterations = 30;
		constexpr float maxIterationsInverse = 1.0f / MaxIterations;

		if (!_disablePaint)
			painter.fillScreen(Color::black());

		for(unsigned int y = 0; y < h; ++y)
		{
			float c_im = MaxIm - y*Im_factor;
			
			for(unsigned int x = 0; x < w; ++x)
			{
				const std::complex<float> c{MinRe + x*Re_factor, c_im};
				std::complex<float> z = c;

				bool isInside = true;
				uint8_t n = 0;

				if (!pointBelongsToCardioid(z))
				{
					std::complex<float> prevValues[2];
					for(; n < MaxIterations; ++n)
					{
						if(std::norm(z) > 4.0f)
						{
							isInside = false;
							break;
						}

						z = z * z + c;

						if (z == prevValues[0]) // Cycle of period 2
						{
							n = MaxIterations;
							isInside = true;
							break; // Belongs to the set
						}

						prevValues[0] = prevValues[1];
						prevValues[1] = z;
					}
				}
				else
					n = MaxIterations;

				if (!isInside)
				{
					const float t = (float)n * maxIterationsInverse;
  
					// Use smooth polynomials for r, g, b
					//const int r = (int)(9*(1-t)*t*t*t*255.0f);
					//const int g = (int)(15*(1-t)*(1-t)*t*t*255.0f);
					//const int b =  (int)(8.5*(1-t)*(1-t)*(1-t)*t*255.0f);

					if (!_disablePaint)
						painter.setPixel(x, y, Color::fromHSV(360.0f * t, 255, 255));
				}
			}
		}
	}

private:
	bool _disablePaint = false;
};

DEFINE_SCREEN(SecondScreen) {
	void onDraw(Size /* regionToUpdate */)
	{
		ConcretePainter painter;
		painter.fillScreen(Color::azure());
	}
};

UiHierarchy<TestScreen<PainterImplementation>, SecondScreen<PainterImplementation>> ui;

inline void setupExample()
{
	tftInit();

	ui.toNextScreen();
	ui.toFirstScreen();

	auto start = millis();
	ui.updateCurrentScreen();
	const auto totalTime = millis() - start;

	ui.getScreen<0>().setDisablePaint(true);

	start = millis();
	ui.updateCurrentScreen();
	const auto calculationTime = millis() - start;
	const auto paintTime = totalTime - calculationTime;

	const auto& mainScreen = ui.getScreen<0>();

	Serial.println("Drawing Mandelbrot set in " + String(mainScreen.width()) + '*' + String(mainScreen.height()));
	Serial.println("Total time: " + String(totalTime) + " ms (" + String((uint32_t)mainScreen.width() * (uint32_t)mainScreen.height() * 1000 / totalTime) + " pixels / second)");
	Serial.println("Calculation time: " + String(calculationTime) + " ms (" + String((uint32_t)mainScreen.width() * (uint32_t)mainScreen.height() * 1000 / calculationTime) + " pixels / second)");
	Serial.println("Paint time: " + String(paintTime) + " ms (" + String((uint32_t)mainScreen.width() * (uint32_t)mainScreen.height() * 1000 / paintTime) + " pixels / second)");
}

inline void loopExample()
{
	
}