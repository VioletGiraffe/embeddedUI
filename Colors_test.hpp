#pragma once

template <class ConcretePainter>
class TestScreen: public Screen<ConcretePainter, TestScreen<ConcretePainter>> {

	template <typename U>
	friend class Widget;

public:
	TestScreen() {
	}

protected:

	void onDraw(Size /* regionToUpdate */)
	{
        ConcretePainter painter;

        constexpr int stripeHeight = 1;
        const int numColors = this->height() / stripeHeight;
        for (uint8_t i = 0; i < numColors; ++i)
        {
            painter.fillRect(Point{0, i * stripeHeight}, Size{this->width(), stripeHeight}, Color::fromHSV(i * 360 / numColors, 255, 255));
        }

        painter.fillRect(Point{0, numColors * stripeHeight}, Point{this->width(), this->height()}, Color::black());
	}

private:
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