#pragma once
#include "Core/DataTypes/Box.h"
#include "Core/DataTypes/Vector2.h"
#include <math.h>

namespace core
{

// Box param order
// left -> top -> right -> bottom

// declare
template <typename T>
Box<T> operator+(const Box<T>& a, const Vector2<T>& b);

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

} // namespace core::string