#pragma once
#include "IInputSystem.h"
#include <memory>

namespace inputs
{

class INativeInputAPI;

class InputSystem final: public IInputSystem
{
public:
	// In initialization of every systems, gameclock must be first
	InputSystem(
		std::unique_ptr<INativeInputAPI> i_nativeInputAPI
	);
	// Inherited via IInputSystem
	void Initialize() override;
	void UpdateInput(const const core::Duration& dt) override;
	void Pause() override;
	void Resume() override;
	void Shutdown() override;

	// Inherited via IInputAPI
	bool IsKeyDown(const KeyboardKey i_key) override;
	bool IsKeyUp(const KeyboardKey i_key) override;
	bool IsKeyPressed(const KeyboardKey i_key) override;
	bool IsKeyRelease(const KeyboardKey i_key) override;
	bool IsKeyHold(const KeyboardKey i_key) override;

private:
	std::unique_ptr<INativeInputAPI> m_nativeInputAPI;
};

} // namespace inputs