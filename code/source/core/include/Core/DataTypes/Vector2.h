#pragma once
#include <cstdint>

namespace data_types
{

template <typename T>
struct Vector2
{
	T x;
	T y;
};
using Vector2F = Vector2<float>;
using Vector2I64 = Vector2<int64_t>;

float GetLength(const Vector2F& i_vector);

// template funcs
template <typename T>
Vector2<T> Add(const Vector2<T>& a, const Vector2<T>& b);

template <typename T>
Vector2<T> Add(const Vector2<T>& a, const Vector2<T>& b)
{
	return Vector2<T>{a.x + b.x, a.y + b.y};
}

} // namespace data_types