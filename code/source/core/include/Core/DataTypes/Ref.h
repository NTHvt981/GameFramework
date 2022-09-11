#pragma once
#include <memory>

namespace data_types
{

template <typename T>
using Ref = std::reference_wrapper<T>;

template <typename T>
using MakeRef = std::ref<T>;

template <typename T>
using MakeCRef = std::cref<const T>;

} // namespace data_types