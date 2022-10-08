#pragma once
#include "Core/DataTypes/Size.h"
#include <math.h>

namespace core
{

// Size param order
// width -> height

// declare
template <typename T>
Size<T> operator*(const Size<T>& a, const float b);
template <typename T>
Size<T> operator/(const Size<T>& a, const float b);
template <typename V, typename T>
Size<T> CastSize(const Size<V>& a);

// impl
template <typename T>
Size<T> operator*(const Size<T>& a, const float b)
{
	return Size<T>
	{
		a.width* b,
		a.height* b
	};
}

template <typename T>
Size<T> operator/(const Size<T>& a, const float b)
{
	return Size<T>
	{
		a.width / b,
		a.height / b
	};
}

template<typename V, typename T>
Size<T> CastSize(const Size<V>& a)
{
	return Size<T>(
		static_cast<T>(a.width),
		static_cast<T>(a.height)
	);
}

} // namespace core::string