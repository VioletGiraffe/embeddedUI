#pragma once

#include <stdint.h>

class Color
{
public:
	inline Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) : _r(r), _g(g), _b(b) {};

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

private:
	inline static uint16_t to565(uint8_t ch1, uint8_t ch2, uint8_t ch3) {
		return ((static_cast<uint16_t>(ch1) >> 3) << 11) | ((static_cast<uint16_t>(ch2) >> 2) << 5) | (static_cast<uint16_t>(ch3) >> 3);
	}

	inline static uint32_t to32bit(uint8_t ch1, uint8_t ch2, uint8_t ch3) {
		return (static_cast<uint32_t>(ch1) << 16) | (static_cast<uint32_t>(ch2) << 8) | static_cast<uint32_t>(ch3);
	}

private:
	uint8_t _r = 0, _g = 0, _b = 0;
};
