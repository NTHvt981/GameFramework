#pragma once

#include <stdlib.h>
#include <cmath>

class CUtils
{
public:

	/// <summary>
	/// chance
	/// </summary>
	/// <param name="chance">0 -> 1</param>
	static bool lottery(float chance);

	static int64_t randRange(int64_t a, int64_t b);

	static float randFloatRange(int64_t a, int64_t b);

	static float getAngle(float x, float y);
};

