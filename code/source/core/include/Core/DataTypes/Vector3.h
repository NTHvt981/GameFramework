#pragma once
#include <cstdint>

namespace core
{

template <typename T>
struct Vector3
{
	static_assert(std::is_arithmetic<T>::value);
	T x;
	T y;
	T z;
};
using Vector3F = Vector3<float>;
using Vector3I = Vector3<int64_t>;

} // namespace core