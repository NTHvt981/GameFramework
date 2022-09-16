#pragma once
#include "Core/DataTypes/Vector2.h"
#include <math.h>

namespace data_types
{

// declare
template <typename T>
Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b);
template <typename T>
Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b);
template <typename T>
bool operator==(const Vector2<T>& a, const Vector2<T>& b);
template <typename T>
Vector2<T> operator*(const Vector2<T>& a, const float b);
template <typename T>
Vector2<T> operator/(const Vector2<T>& a, const float b);
template <typename T>
float GetLength(const Vector2<T>& i_vector);

// impl
template <typename T>
Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b)
{
	return Vector2<T>{a.x + b.x, a.y + b.y};
}

template <typename T>
Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b)
{
	return Vector2<T>{a.x - b.x, a.y - b.y};
}

template <typename T>
bool operator==(const Vector2<T>& a, const Vector2<T>& b)
{
	return (a.x == b.x) && (a.y == b.y);
}

template <typename T>
Vector2<T> operator*(const Vector2<T>& a, const float b)
{
	return Vector2<T>{a.x* b, a.y* b};
}

template <typename T>
Vector2<T> operator/(const Vector2<T>& a, const float b)
{
	return Vector2<T>{a.x / b, a.y / b};
}

template <typename T>
float GetLength(const Vector2<T>& i_vector)
{
	return sqrtf(powf(i_vector.x, 2) + powf(i_vector.y, 2));
}

} // namespace data_types::string