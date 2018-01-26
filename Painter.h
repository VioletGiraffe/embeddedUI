#pragma once

#include "Size.h"
#include "Color.h"

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

template <class ConcreteImplementation>
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
		this->fillRect(Point(0, 0), Size(displayWidth(), displayHeight()), color);
	}
};
