#pragma once
#include "Core/DataTypes/Box.h"
#include "Core/DataTypes/Size.h"
#include "Core/DataTypes/Vector2.h"
#include <math.h>

namespace core
{

// Size param order
// width -> height

// declare
template <typename T>
Size<T> ToSize(const Box<T>& a);

// impl
template <typename T>
Size<T> ToSize(const Box<T>& a)
{
	return Size<T>
	{
		a.right + a.left,
		a.bottom + a.top
	};
}

template <typename T>
Box<T> operator+(Vector2<T> vector, Size<T> size)
{
	return Box<T>
	{
		vector.x,
		vector.y,
		vector.x + size.width,
		vector.y + size.height
	};
}

} // namespace core