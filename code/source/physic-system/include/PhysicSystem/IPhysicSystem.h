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

	virtual void PreFixedUpdate(const uint64_t dt) = 0;
	virtual void FixedUpdate(const uint64_t dt) = 0;
	virtual void PostFixedUpdate(const uint64_t dt) = 0;

	virtual void SetCollisionCheckFilter(const core::BoxF i_boundary) = 0;
	virtual void RemoveCollisionCheckFilter() = 0;
};

} // namespace physics