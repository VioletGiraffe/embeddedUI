#pragma once

#include "Size.h"
#include "Color.h"

#include <type_traits>

class AbstractPainter
{
public:
	template <typename T = void>
	void rect(const Point& topLeft, const Size& size, const Color& color) {
		static_assert(!std::is_same<T, void>::value, "This method must be implemented by a subclass");
	}

	template <typename T = void>
	void rect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		static_assert(!std::is_same<T, void>::value, "This method must be implemented by a subclass");
	}

	template <typename T = void>
	void fillRect(const Point& topLeft, const Size& size, const Color& color) {
		static_assert(!std::is_same<T, void>::value, "This method must be implemented by a subclass");
	}

	template <typename T = void>
	void fillRect(const Point& topLeft, const Point& bottomRight, const Color& color) {
		static_assert(!std::is_same<T, void>::value, "This method must be implemented by a subclass");
	}
};

template <class Display, Display& displayInstance>
class DisplayPainter : public AbstractPainter
{
public:
	using DisplayType = Display;

	DisplayPainter() : _display(displayInstance) {}

	template <typename T = void>
	uint16_t displayWidth() const {
		static_assert(!std::is_same<T, void>::value, "This method must be implemented by a subclass");
		return 0;
	}

	template <typename T = void>
	uint16_t displayHeight() const {
		static_assert(!std::is_same<T, void>::value, "This method must be implemented by a subclass");
		return 0;
	}

	template <typename T = void>
	void fillScreen(const Color& color) {
		static_assert(!std::is_same<T, void>::value, "This method must be implemented by a subclass");
	}

protected:
	Display& _display;
};
