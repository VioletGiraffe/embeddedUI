#pragma once

#include "Size.h"

template <class ConcreteWidget>
class Widget
{
public:
	struct Attributes {
		uint8_t frameWidth = 0;
	};

	inline Widget(const Point& topLeft = Point{ 0, 0 }, const Size& size = Size{ 0, 0 }) : _topLeft(topLeft), _size(size) {}

	inline const Attributes& attributes() const {
		return _attributes;
	}

	inline void setAttributes(const Attributes& attrs) {
		_attributes = attrs;
	}

	inline Point topLeft() const {
		return _topLeft;
	}

	inline Size size() const {
		return _size;
	}

protected:
	// Events
	inline void onDraw() {
		onDraw(_size);
	}

	void onDraw(Size regionToUpdate) {
		static_cast<ConcreteWidget*>(this)->onDraw(regionToUpdate);
	}

private:
	Attributes _attributes;
	Point _topLeft;
	Size _size;
};
