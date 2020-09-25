#include "Vector.h"

Vector::Vector()
{
	x = 0;
	y = 0;
}

Vector::Vector(float _x , float _y )
{
	x = _x;
	y = _y;
}

Vector Add(Vector a, Vector b)
{
	Vector c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;

	return c;
}

Vector Vector::operator+(Vector b)
{
	return Vector(this->x + b.x, this->y + b.y);
}
