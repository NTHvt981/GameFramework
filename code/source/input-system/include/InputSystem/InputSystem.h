#pragma once
#include "IInputSystem.h"
#include "API/INativeInputAPI.h"
#include <memory>

namespace input
{

class InputSystem final: public IInputSystem
{
public:
	// In initialization of every systems, gameclock must be first
	InputSystem(
		std::shared_ptr<INativeInputAPI> i_nativeInputAPI
	);
	// Inherited via IInputSystem
	void Initialize() override;
	void UpdateInput(const uint64_t dt) override;
	void Pause() override;
	void Resume() override;
	void Shutdown() override;

private:
	std::shared_ptr<INativeInputAPI> m_nativeInputAPI;
};

} // namespace input