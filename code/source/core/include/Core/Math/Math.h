#pragma once
#include <cmath>

namespace core
{

template<typename T>
T Sign(const T magnitude)
{
	if (magnitude > 0)
	{
		return 1;
	}
	else if (magnitude < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

template<typename T>
bool IsOverlap(const Box<T> a, const Box<T> b)
{
	return (
		a.right <= b.left ||
		b.right <= a.left ||
		a.bottom <= b.top ||
		b.bottom <= a.top
		) == false;
}

} // namespace core