#pragma once
#include "Core/DataTypes/Box.h"
#include <math.h>

namespace core
{

// Box param order
// left -> top -> right -> bottom

// declare
template <typename T>
Box<T> operator+(const Box<T>& a, const Box<T>& b);
template <typename T>
Box<T> operator*(const Box<T>& a, const float b);
template <typename T>
Box<T> operator/(const Box<T>& a, const float b);

// impl
template <typename T>
Box<T> operator+(const Box<T>& a, const Box<T>& b)
{
	return Box<T>
	{
		a.left + b.left,
		a.top + b.top,
		a.right + b.right,
		a.bottom + b.bottom,
	};
}

template <typename T>
Box<T> operator*(const Box<T>& a, const float b)
{
	return Box<T>
	{
		a.left * b,
		a.top * b,
		a.right * b,
		a.bottom * b,
	};
}

template <typename T>
Box<T> operator/(const Box<T>& a, const float b)
{

	return Box<T>
	{
		a.left / b,
		a.top / b,
		a.right / b,
		a.bottom / b,
	};
}

} // namespace core::string