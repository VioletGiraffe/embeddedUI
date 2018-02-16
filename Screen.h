#pragma once

#include "Widget.h"

template <class ConcretePainter>
class Screen : public Widget<Screen<ConcretePainter>>
{
public:
	Screen() {
		this->_size = Size(ConcretePainter::screenWidth(), ConcretePainter::screenHeight());
	}

protected:
	void onDraw() {
		ConcretePainter painter;
		painter.fillRect({0, 0}, this->_size, Color(0, 127, 255));
	}
};