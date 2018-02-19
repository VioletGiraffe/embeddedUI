#pragma once

#include "Widget.h"

// A widget that is the size of the whole screen

template <class ConcretePainter>
class Screen : public Widget<Screen<ConcretePainter>>
{
public:
	Screen() : Widget<Screen<ConcretePainter>>(Point{0, 0}, Size{ConcretePainter::screenWidth(), ConcretePainter::screenHeight()})  {
	}
};