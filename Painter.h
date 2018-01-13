#pragma once

#include "default_constructible_ref.hpp"
#include "DisplayAdapter.h"

template<typename U, DisplayAdapter<U>& displayAdapter>
class Painter
{
public:

};

template <class ConcreteDisplayAdapterType, typename ConcretePainter = Painter<typename ConcreteDisplayAdapterType::DisplayType, ConcreteDisplayAdapterType&>>
class PainterFabricTemplate
{
public:
	static void init(ConcreteDisplayAdapterType& display) {
		_display = display;
	}

	static ConcretePainter createPainter() {
		return ConcretePainter(_display);
	}

private:
	static default_constructible_ref<ConcreteDisplayAdapterType> _display;
};
