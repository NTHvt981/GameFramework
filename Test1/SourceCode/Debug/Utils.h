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

	static int randRange(int a, int b);

	static float randFloatRange(int a, int b);

	static float getAngle(float x, float y);
};

