#pragma once
#include "IInputSystem.h"
#include "Core/APIs/INativeInputAPI.h"
#include <memory>

namespace logic
{

class InputSystem final: public IInputSystem
{
public:
	// In initialization of every systems, gameclock must be first
	InputSystem(
		std::unique_ptr<core::INativeInputAPI> i_nativeInputAPI
	);
	// Inherited via IInputSystem
	void Initialize() override;
	void UpdateInput(const core::Duration& dt) override;
	void Pause() override;
	void Resume() override;
	void Shutdown() override;

	// Inherited via IInputAPI
	bool IsKeyDown(const core::KeyboardKey i_key) const override;
	bool IsKeyUp(const core::KeyboardKey i_key) const override;
	bool IsKeyPressed(const core::KeyboardKey i_key) const override;
	bool IsKeyRelease(const core::KeyboardKey i_key) const override;
	bool IsKeyHold(const core::KeyboardKey i_key) const override;

private:
	std::unique_ptr<core::INativeInputAPI> m_nativeInputAPI;
};

} // namespace logic