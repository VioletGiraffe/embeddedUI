#pragma once

#include "Widget.h"

// A widget that is the size of the whole screen

template <class ConcretePainter, class ConcreteScreen>
class Screen : public Widget<ConcreteScreen>
{
public:
	Screen() : Widget<ConcreteScreen>(Point{0, 0}, Size{ConcretePainter::screenWidth(), ConcretePainter::screenHeight()})  {
	}
};