#pragma once
#include "Core/APIs/IInputAPI.h"
#include "Core/DataTypes/Duration.h"

namespace logic
{

class IInputSystem : public core::IInputAPI
{
public:
	virtual void Initialize() = 0;
	virtual void UpdateInput(const core::Duration& dt) = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Shutdown() = 0;
};

} // namespace logic