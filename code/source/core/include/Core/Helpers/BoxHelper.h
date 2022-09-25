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

BoxF ToFloat(const BoxI64& a);

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

BoxF core::ToFloat(const BoxI64& a)
{
	return BoxF
	{
		float(a.left),
		float(a.top),
		float(a.right),
		float(a.bottom)
	};
}

} // namespace core::string