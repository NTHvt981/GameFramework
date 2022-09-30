#pragma once
#include <cstdint>
#include <type_traits>

namespace core
{

template <typename T>
struct Vector2
{
	static_assert(std::is_arithmetic<T>::value);
	T x = 0;
	T y = 0;
};
using Vector2F = Vector2<float>;
using Vector2I64 = Vector2<int64_t>;

} // namespace core