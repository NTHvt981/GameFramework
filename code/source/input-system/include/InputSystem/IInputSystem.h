#pragma once
#include "API/IInputAPI.h"

namespace input
{

class IInputSystem : public IInputAPI
{
public:
	virtual void Initialize() = 0;
	virtual void UpdateInput(const uint64_t dt) = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Shutdown() = 0;
};

} // namespace input