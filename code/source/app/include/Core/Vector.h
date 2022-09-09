#pragma once

#include <cmath>

class Vector {
public:
	float x;
	float y;
	
public:
	Vector(float _x = 0, float _y = 0);
	Vector operator+(Vector b);
	Vector operator/(int64_t d);

	float Length();

	void Set(float _x, float _y);
};

Vector Add(Vector a, Vector b);