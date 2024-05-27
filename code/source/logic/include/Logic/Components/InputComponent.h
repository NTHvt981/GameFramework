#pragma once
#include "IComponent.h"
#include "Core/DataTypes/KeyboardKey.h"
#include "Core/APIs/IInputAPI.h"
#include <stdint.h>
#include <memory>
	
namespace logic
{

static constexpr core::ComponentKey sk_inputComponentKey = "InputComponent";

class InputComponent final : public IComponent
{
public:
	InputComponent(std::shared_ptr<core::IInputAPI> i_inputAPI);

	// Inherited via Component
	void Register() override {};
	void Deregister() override {};

	bool IsKeyDown(const core::KeyboardKey i_key);
	bool IsKeyUp(const core::KeyboardKey i_key);
	bool IsKeyPressed(const core::KeyboardKey i_key);
	bool IsKeyRelease(const core::KeyboardKey i_key);
	bool IsKeyHold(const core::KeyboardKey i_key);

private:
	const core::IInputAPI& m_inputAPI;
};

} // namespace logic