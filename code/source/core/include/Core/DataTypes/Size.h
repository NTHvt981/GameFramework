#pragma once
#include <cstdint>

namespace data_types
{

template <typename T>
struct Size
{
	T width;
	T height;
};
using SizeF = Size<float>;
using SizeI64 = Size<int64_t>;

} // namespace data_types
