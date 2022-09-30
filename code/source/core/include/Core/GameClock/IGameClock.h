#pragma once
#include "Core/Signals/Signal.h"
#include "Core/DataTypes/Duration.h"
#include <stdint.h>

namespace core::logic
{

class IGameClock
{
public:
	signals::Signal<const core::Duration&> sig_onUpdateInput;
	signals::Signal<const core::Duration&> sig_onPreFixedUpdate;
	signals::Signal<const core::Duration&> sig_onFixedUpdate;
	signals::Signal<const core::Duration&> sig_onPostFixedUpdate;
	signals::Signal<const core::Duration&> sig_onPreUpdate;
	signals::Signal<const core::Duration&> sig_onUpdate;
	signals::Signal<const core::Duration&> sig_onPostUpdate;
	signals::Signal<const core::Duration&> sig_onPreRender;
	signals::Signal<const core::Duration&> sig_onRender;
	signals::Signal<const core::Duration&> sig_onPostRender;
};

} // namespace core::logic