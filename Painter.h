#pragma once

#include "default_constructible_ref.hpp"

#include <type_traits>

class AbstractPainter
{
};

template <class Display, Display& displayInstance>
class DisplayPainter : public AbstractPainter
{
public:
	using DisplayType = Display;

	DisplayPainter() : _display(displayInstance) {}

protected:
	Display& _display;
};

// template <class ConcretePainter>
// class BasicPainter : public ConcretePainter
// {
// 	static_assert(std::is_base_of<AbstractPainter, ConcretePainter>::value, "ConcretePainter must inherit AbstractPainter.");
// 
// public:
// 
// };

