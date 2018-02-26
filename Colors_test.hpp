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
		static const Color colors[] = {
            Color::red(),
            Color::orange(),
            Color::yellow(),
            Color::green(),
            Color::cyan(),
            Color::blue(),
            Color::violet()
        };

        ConcretePainter painter;

        constexpr int numColors = sizeof(colors)/sizeof(colors[0]);
        const int stripeHeight = this->height() / numColors;
        for (uint8_t i = 0; i < numColors; ++i)
        {
            painter.fillRect(Point{0, i * stripeHeight}, Size{this->width(), stripeHeight}, colors[i]);
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