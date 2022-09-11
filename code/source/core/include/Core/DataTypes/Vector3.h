#pragma once
#include <cstdint>

namespace data_types
{

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;
};
using Vector3F = Vector3<float>;
using Vector3I = Vector3<int64_t>;

} // namespace data_types