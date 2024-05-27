#include "Logic/Components/InputComponent.h"
#include "Core/APIs/IInputAPI.h"
#include "Core/DataTypes/KeyboardKey.h"

namespace logic
{

InputComponent::InputComponent(std::shared_ptr<core::IInputAPI> i_inputAPI)
	: m_inputAPI(*i_inputAPI.get())
{
}

bool InputComponent::IsKeyDown(const core::KeyboardKey i_key)
{
	return m_inputAPI.IsKeyDown(i_key);
}

bool InputComponent::IsKeyUp(const core::KeyboardKey i_key)
{
	return m_inputAPI.IsKeyUp(i_key);
}

bool InputComponent::IsKeyPressed(const core::KeyboardKey i_key)
{
	return m_inputAPI.IsKeyPressed(i_key);
}

bool InputComponent::IsKeyRelease(const core::KeyboardKey i_key)
{
	return m_inputAPI.IsKeyRelease(i_key);
}

bool InputComponent::IsKeyHold(const core::KeyboardKey i_key)
{
	return m_inputAPI.IsKeyHold(i_key);
}

} // namespace logic