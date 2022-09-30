#pragma once
#include "API/IInputAPI.h"
#include "Core/DataTypes/Duration.h"

namespace inputs
{

class IInputSystem : public IInputAPI
{
public:
	virtual void Initialize() = 0;
	virtual void UpdateInput(const const core::Duration& dt) = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Shutdown() = 0;
};

} // namespace inputs