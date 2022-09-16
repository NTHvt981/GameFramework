#pragma once
#include "Core/DataTypes/Box.h"
#include "Core/DataTypes/Size.h"
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

} // namespace core