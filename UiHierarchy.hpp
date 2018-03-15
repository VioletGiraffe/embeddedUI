#pragma once

#include "Widget.h"
#include <tuple/tuple_helpers.hpp>

#include <tuple>

template <class... ListOfScreenTypes>
class UiHierarchy {
public:
	UiHierarchy() = default;

	template <size_t index>
	auto& getScreen()
	{
		return std::get<index>(_screens);
	}

	void updateAll()
	{
		tuple::for_each([](auto& screen){
			screen.update();
		}, _screens);
	}

private:
	std::tuple<ListOfScreenTypes...> _screens;
};