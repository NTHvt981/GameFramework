#pragma once
#include <cmath>

namespace math
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

} // namespace math