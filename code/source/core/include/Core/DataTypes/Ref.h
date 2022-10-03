#pragma once
#include <memory>

namespace core
{

template <typename T>
using Ref = std::reference_wrapper<T>;

//template <typename T>
//using MakeCRef = std::cref<const T>;

} // namespace core