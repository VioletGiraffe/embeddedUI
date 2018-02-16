#pragma once

#include "Painter.h"

#ifndef SSD1351_COLORORDER_RGB // Adafruit_SSD1351.h lacks its own include guard
#include <Adafruit_SSD1351.h>
#endif

class PainterAdafruitSsd1351 : public DisplayPainter<PainterAdafruitSsd1351, Adafruit_SSD1351>
{
public:
	void rect(const Point& topLeft, const Size& size, const Color& color) {
		_displayInstance.get().drawRect(topLeft.x(), topLeft.y(), size.width(), size.height(), color.toRgb565());
	}

	void rect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		_displayInstance.get().drawRect(topLeft.x(), topLeft.y(), bottomRight.x() - topLeft.x(), bottomRight.y() - topLeft.y(), color.toRgb565());
	}

	void fillRect(const Point& topLeft, const Size& size, const Color& color) {
		_displayInstance.get().fillRect(topLeft.x(), topLeft.y(), size.width(), size.height(), color.toRgb565());
	}

	void fillRect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		_displayInstance.get().fillRect(topLeft.x(), topLeft.y(), bottomRight.x() - topLeft.x(), bottomRight.y() - topLeft.y(), color.toRgb565());
	}

	static uint16_t screenWidth() {
		return static_cast<uint16_t>(_displayInstance.get().width());
	}

	static uint16_t screenHeight() {
		return static_cast<uint16_t>(_displayInstance.get().height());
	}
};