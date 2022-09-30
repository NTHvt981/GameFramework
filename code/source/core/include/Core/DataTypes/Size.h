#pragma once
#include <cstdint>

namespace core
{

template <typename T>
struct Size
{
	static_assert(std::is_arithmetic<T>::value);
	T width;
	T height;
};
using SizeF = Size<float>;
using SizeI64 = Size<int64_t>;

} // namespace core
