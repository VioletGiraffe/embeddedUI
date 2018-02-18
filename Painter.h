#pragma once

#include "Size.h"
#include "Color.h"

#include "default_constructible_ref.hpp"

template <class ConcreteImplementation>
class AbstractPainter
{
public:
	void rect(const Point& topLeft, const Size& size, const Color& color) {
		static_cast<ConcreteImplementation&>(*this).rect(topLeft, size, color);
	}

	void rect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		static_cast<ConcreteImplementation&>(*this).rect(topLeft, bottomRight, color);
	}

	void fillRect(const Point& topLeft, const Size& size, const Color& color) {
		static_cast<ConcreteImplementation&>(*this).fillRect(topLeft, size, color);
	}

	void fillRect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		static_cast<ConcreteImplementation&>(*this).fillRect(topLeft, bottomRight, color);
	}
};

template <class ConcreteImplementation, class DisplayType>
class DisplayPainter : public AbstractPainter<ConcreteImplementation>
{
public:
	uint16_t displayWidth() const {
		return static_cast<const ConcreteImplementation&>(*this).displayWidth();
	}

	uint16_t displayHeight() const {
		return static_cast<const ConcreteImplementation&>(*this).displayHeight();
	}

	void fillScreen(const Color& color) {
		static_cast<const ConcreteImplementation&>(*this).fillScreen();
	}

	static void setDisplayInstance(DisplayType& instance) {
		_displayInstance = instance;
	}

protected:
	static default_constructible_ref<DisplayType> _displayInstance;
};

template <class ConcreteImplementation, class DisplayType>
default_constructible_ref<DisplayType> DisplayPainter<ConcreteImplementation, DisplayType>::_displayInstance;
