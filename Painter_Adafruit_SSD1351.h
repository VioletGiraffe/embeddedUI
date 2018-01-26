#pragma once

#include "Painter.h"

#ifndef SSD1351_COLORORDER_RGB // Adafruit_SSD1351.h lacks its own include guard
#include <Adafruit_SSD1351.h>
#endif

template <Adafruit_SSD1351& displayInstance>
class PainterAdafruitSsd1351 : public DisplayPainter<PainterAdafruitSsd1351<displayInstance>>
{
public:
	void rect(const Point& topLeft, const Size& size, const Color& color) {
		displayInstance.drawRect(topLeft.x(), topLeft.y(), size.width(), size.height(), color.toRgb565());
	}

	void rect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		displayInstance.drawRect(topLeft.x(), topLeft.y(), bottomRight.x() - topLeft.x(), bottomRight.y() - topLeft.y(), color.toRgb565());
	}

	void fillRect(const Point& topLeft, const Size& size, const Color& color) {
		displayInstance.fillRect(topLeft.x(), topLeft.y(), size.width(), size.height(), color.toRgb565());
	}

	void fillRect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		displayInstance.fillRect(topLeft.x(), topLeft.y(), bottomRight.x() - topLeft.x(), bottomRight.y() - topLeft.y(), color.toRgb565());
	}

	uint16_t displayWidth() const {
		return static_cast<uint16_t>(displayInstance.width());
	}

	uint16_t displayHeight() const {
		return static_cast<uint16_t>(displayInstance.height());
	}
};