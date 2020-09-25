#pragma once

class Vector {
public:
	float x;
	float y;
	
public:
	Vector();
	Vector(float _x , float _y );
	Vector operator+(Vector b);
};

Vector Add(Vector a, Vector b);