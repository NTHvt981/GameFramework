#pragma once
#include <cstdint>

namespace core
{

template <typename T>
struct Box
{
	T left = 0;
	T top = 0;
	T right = 0;
	T bottom = 0;
};
using BoxF = Box<float>;
using BoxI64 = Box<int64_t>;

} // namespace core
