#pragma once
#include "IPhysicAPI.h"
#include "Core/Signals/Signal.h"
#include "Core/DataTypes/Duration.h"

namespace physics
{

class IPhysicSystem: public IPhysicAPI
{
public:
	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;

	virtual void PreFixedUpdate(const core::Duration& dt) = 0;
	virtual void FixedUpdate(const core::Duration& dt) = 0;
	virtual void PostFixedUpdate(const core::Duration& dt) = 0;

	virtual void SetCollisionCheckFilter(const core::BoxF i_boundary) = 0;
	virtual void RemoveCollisionCheckFilter() = 0;
};

} // namespace physics