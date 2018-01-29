#pragma once

template <typename T>
struct default_constructible_ref
{
	default_constructible_ref() = default;
	default_constructible_ref(T& ref) : _ref(&ref) {}
	default_constructible_ref(const default_constructible_ref& other) = default;
	default_constructible_ref& operator=(const default_constructible_ref& other) = default;

	operator bool() const {
		return _ref != nullptr;
	}

	T& get() {
		return *_ref;
	}

	const T& get() const {
		return *_ref;
	}

private:
	T * _ref = nullptr;
};

template <typename T>
struct default_constructible_cref
{
	default_constructible_cref() = default;
	default_constructible_cref(const T& ref) : _ref(&ref) {}
	default_constructible_cref(const default_constructible_cref& other) = default;
	default_constructible_cref& operator=(const default_constructible_cref& other) = default;

	operator bool() const {
		return _ref != nullptr;
	}

	const T& get() const {
		return *_ref;
	}

private:
	const T* _ref = nullptr;
};

