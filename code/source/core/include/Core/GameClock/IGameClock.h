#pragma once
#include "Core/Signals/Signal.h"
#include <stdint.h>

namespace core::logic
{

class IGameClock
{
public:
	signals::Signal<const uint64_t> sig_onUpdateInput;
	signals::Signal<const uint64_t> sig_onPreFixedUpdate;
	signals::Signal<const uint64_t> sig_onFixedUpdate;
	signals::Signal<const uint64_t> sig_onPostFixedUpdate;
	signals::Signal<const uint64_t> sig_onPreUpdate;
	signals::Signal<const uint64_t> sig_onUpdate;
	signals::Signal<const uint64_t> sig_onPostUpdate;
	signals::Signal<const uint64_t> sig_onPreRender;
	signals::Signal<const uint64_t> sig_onRender;
	signals::Signal<const uint64_t> sig_onPostRender;
};

} // namespace core::logic