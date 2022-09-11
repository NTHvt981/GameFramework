#pragma once
#include <cstdint>

namespace data_types
{

template <typename T>
struct Box
{
	T left;
	T top;
	T right;
	T bottom;
};
using BoxF = Box<float>;
using BoxI64 = Box<int64_t>;

} // namespace data_types
