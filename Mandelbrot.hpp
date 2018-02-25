#pragma once

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

				if (!isInside)
				{
					const float t = (float)n * maxIterationsInverse;
  
					// Use smooth polynomials for r, g, b
					const int r = (int)(9*(1-t)*t*t*t*255.0f);
					const int g = (int)(15*(1-t)*(1-t)*t*t*255.0f);
					const int b =  (int)(8.5*(1-t)*(1-t)*(1-t)*t*255.0f);
					painter.setPixel(x, y, Color(r, g, b));
				}
			}
		}
	}
};

TestScreen<PainterImplementation> screen;

inline void setupExample()
{
	tftInit();
	screen.update();
}

inline void loopExample()
{
	
}