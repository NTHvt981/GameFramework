#pragma once
#include <cstdint>

namespace data_types
{

template <typename T>
struct Vector2
{
	T x = 0;
	T y = 0;
};
using Vector2F = Vector2<float>;
using Vector2I64 = Vector2<int64_t>;

} // namespace data_types