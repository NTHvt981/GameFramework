#pragma once
#include "Core/DataTypes/Box.h"
#include "Core/DataTypes/Vector2.h"
#include <math.h>

namespace data_types
{

// Box param order
// left -> top -> right -> bottom

// declare
template <typename T>
Box<T> operator+(const Box<T>& a, const Box<T>& b);
template <typename T>
Box<T> operator+(const Box<T>& a, const Vector2<T>& b);
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
Box<T> operator+(const Box<T>& a, const Vector2<T>& b)
{
	return Box<T>
	{
		a.left + b.x,
		a.top + b.y,
		a.right + b.x,
		a.bottom + b.y,
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

} // namespace data_types::string