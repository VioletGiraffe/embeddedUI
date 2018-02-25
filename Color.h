#pragma once

#include <stdint.h>

#define DEFINE_COLOR(name, r, g, b) \
	inline static const Color name() {\
	  return Color{r, g, b};\
   }

class Color
{
public:
	inline explicit Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) : _r(r), _g(g), _b(b) {};

	inline uint16_t toRgb565() const {
		return to565(_r, _g, _b);
	}

	inline uint16_t toBgr565() const {
		return to565(_b, _g, _r);
	}

	inline uint32_t toRgb() const {
		return to32bit(_r, _g, _b);
	}

	inline uint32_t toBgr() const {
		return to32bit(_b, _g, _r);
	}

// Predefined colors
	// Grayscale
	DEFINE_COLOR(black, 0, 0, 0)
	DEFINE_COLOR(darkGrey, 64, 64, 64)
	DEFINE_COLOR(grey, 127, 127, 127)
	DEFINE_COLOR(white, 255, 255, 255)

	// Dark shades
	DEFINE_COLOR(maroon, 128, 0, 0)
	DEFINE_COLOR(darkRed, 139, 0, 0)
	DEFINE_COLOR(carmine, 150, 0, 24)
	DEFINE_COLOR(purple, 127, 0, 127)

	// Evenly spaced fully saturated colors colors
	DEFINE_COLOR(red, 255, 0, 0)
	DEFINE_COLOR(orange, 255, 127, 0)
	DEFINE_COLOR(yellow, 255, 255, 0)
	DEFINE_COLOR(lawnGreen, 127, 255, 0)
	DEFINE_COLOR(green, 0, 255, 0)
	DEFINE_COLOR(springGreen, 0, 255, 127)
	DEFINE_COLOR(cyan, 0, 255, 255)
	DEFINE_COLOR(azure, 0, 127, 255)
	DEFINE_COLOR(blue, 0, 0, 255)
	DEFINE_COLOR(violet, 127, 0, 255)
	DEFINE_COLOR(magenta, 255, 0, 255)
	DEFINE_COLOR(pink, 255, 0, 127)

private:
	inline static uint16_t to565(uint8_t ch1, uint8_t ch2, uint8_t ch3) {
		return ((static_cast<uint16_t>(ch1) << 8) | (static_cast<uint16_t>(ch2) << 3) | (static_cast<uint16_t>(ch3) >> 3));
	}

	inline static uint32_t to32bit(uint8_t ch1, uint8_t ch2, uint8_t ch3) {
		return (static_cast<uint32_t>(ch1) << 16) | (static_cast<uint32_t>(ch2) << 8) | static_cast<uint32_t>(ch3);
	}

private:
	uint8_t _r = 0, _g = 0, _b = 0;
};

#undef DEFINE_COLOR // So that this macro is not visible to the client
