#pragma once
#include "IPhysicAPI.h"
#include "Core/Signals/Signal.h"

namespace physics
{

class IPhysicSystem: public IPhysicAPI
{
public:
	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;
	virtual void UpdateDynamicColliderStates() const = 0;

	signals::Signal<ids::EntityId, ids::EntityId> sig_onEntityTouch;
	signals::Signal<ids::EntityId, ids::EntityId> sig_onEntityCollide;
};

} // namespace physics