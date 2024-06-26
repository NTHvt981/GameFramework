#include "Utils.h"

bool CUtils::lottery(float chance) {
	return (rand() % 100) < (chance * 100);
}

int64_t CUtils::randRange(int64_t a, int64_t b)
{
	return a + (rand() % (b - a + 1));
}

float CUtils::randFloatRange(int64_t a, int64_t b)
{
	return randRange(a * 100, b * 100) / 100.0;
}

float CUtils::getAngle(float x, float y)
{
	return atan2(y, x);
}
