#pragma once
#include "IComponent.h"
#include "InputSystem/API/IInputAPI.h"
#include <memory>

namespace logic
{

static constexpr core::ComponentKey sk_inputComponentKey = "InputComponent";

class InputComponent final : public IComponent
{
public:
	InputComponent(std::weak_ptr<input::IInputAPI> i_inputAPI);

	// Inherited via Component
	void Register() override {};
	void Deregister() override {};

	bool IsKeyDown(const input::KeyboardKey i_key);
	bool IsKeyUp(const input::KeyboardKey i_key);
	bool IsKeyPressed(const input::KeyboardKey i_key);
	bool IsKeyRelease(const input::KeyboardKey i_key);
	bool IsKeyHold(const input::KeyboardKey i_key);

private:
	std::weak_ptr<input::IInputAPI> m_inputAPI;
};

} // namespace logic