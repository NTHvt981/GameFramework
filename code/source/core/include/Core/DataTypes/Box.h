#pragma once
#include <cstdint>

namespace core
{

template <typename T>
struct Box
{
	static_assert(std::is_arithmetic<T>::value);
	T left = 0;
	T top = 0;
	T right = 0;
	T bottom = 0;
};
using BoxF = Box<float>;
using BoxI64 = Box<int64_t>;
using BoxUI64 = Box<uint64_t>;

} // namespace core
