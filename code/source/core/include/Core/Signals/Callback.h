#pragma once
#include <functional>

namespace signals
{

template<class ...Args>
using Callback = std::function<void(Args...)>;

} // namespace signals
