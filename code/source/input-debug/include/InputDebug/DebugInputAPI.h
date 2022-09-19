#pragma once
#include "InputSystem/API/INativeInputAPI.h"

namespace input
{

class DebugInputAPI final : public INativeInputAPI
{
public:

	// Inherited via INativeInputAPI
	void Initialize() override;
	void UpdateInput() override;
	void Pause() override;
	void Resume() override;
	void ShutDown() override;
	bool IsKeyDown(const KeyboardKey i_key) override;
	bool IsKeyUp(const KeyboardKey i_key) override;
	bool IsKeyPressed(const KeyboardKey i_key) override;
	bool IsKeyRelease(const KeyboardKey i_key) override;
	bool IsKeyHold(const KeyboardKey i_key) override;
};

} // namespace input