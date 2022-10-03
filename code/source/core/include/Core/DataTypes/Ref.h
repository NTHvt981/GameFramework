#pragma once
#include <memory>

namespace core
{

template <typename T>
using Ref = std::reference_wrapper<T>;

} // namespace core