#pragma once

#include "Painter.h"

template <class ConcretePainter, class DisplayType>
class PainterAdafruitBase : public DisplayPainter<ConcretePainter, DisplayType>
{
	using Parent = DisplayPainter<ConcretePainter, DisplayType>;
public:
	void rect(const Point& topLeft, const Size& size, const Color& color) {
		Parent::_displayInstance.get().drawRect(topLeft.x(), topLeft.y(), size.width(), size.height(), color.toRgb565());
	}

	void rect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		Parent::_displayInstance.get().drawRect(topLeft.x(), topLeft.y(), bottomRight.x() - topLeft.x(), bottomRight.y() - topLeft.y(), color.toRgb565());
	}

	void fillRect(const Point& topLeft, const Size& size, const Color& color) {
		Parent::_displayInstance.get().fillRect(topLeft.x(), topLeft.y(), size.width(), size.height(), color.toRgb565());
	}

	void fillRect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		Parent::_displayInstance.get().fillRect(topLeft.x(), topLeft.y(), bottomRight.x() - topLeft.x(), bottomRight.y() - topLeft.y(), color.toRgb565());
	}

	void fillScreen(const Color& color) {
		Parent::_displayInstance.get().fillScreen(color.toRgb565());
	}

	void setPixel(const Point& pixel, const Color& color) {
		Parent::_displayInstance.get().drawPixel(pixel.x(), pixel.y(), color.toRgb565());
	}

	void setPixel(uint16_t x, uint16_t y, const Color& color) {
		setPixel(Point{x, y}, color);
	}

	static uint16_t screenWidth() {
		return static_cast<uint16_t>(Parent::_displayInstance.get().width());
	}

	static uint16_t screenHeight() {
		return static_cast<uint16_t>(Parent::_displayInstance.get().height());
	}
};