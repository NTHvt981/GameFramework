#include "Logic/Components/InputComponent.h"
#include "InputSystem/API/IInputAPI.h"
#include "InputSystem/DataTypes/KeyboardKey.h"

namespace logic
{

InputComponent::InputComponent(std::shared_ptr<inputs::IInputAPI> i_inputAPI)
	: m_inputAPI(*i_inputAPI.get())
{
}

bool InputComponent::IsKeyDown(const inputs::KeyboardKey i_key)
{
	return m_inputAPI.IsKeyDown(i_key);
}

bool InputComponent::IsKeyUp(const inputs::KeyboardKey i_key)
{
	return m_inputAPI.IsKeyUp(i_key);
}

bool InputComponent::IsKeyPressed(const inputs::KeyboardKey i_key)
{
	return m_inputAPI.IsKeyPressed(i_key);
}

bool InputComponent::IsKeyRelease(const inputs::KeyboardKey i_key)
{
	return m_inputAPI.IsKeyRelease(i_key);
}

bool InputComponent::IsKeyHold(const inputs::KeyboardKey i_key)
{
	return m_inputAPI.IsKeyHold(i_key);
}

} // namespace logic