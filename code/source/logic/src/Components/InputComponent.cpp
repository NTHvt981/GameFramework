#include "Logic/Components/InputComponent.h"
#include "InputSystem/API/IInputAPI.h"
#include "InputSystem/DataTypes/KeyboardKey.h"

namespace logic
{

InputComponent::InputComponent(std::weak_ptr<inputs::IInputAPI> i_inputAPI)
	: m_inputAPI(i_inputAPI)
{
}

bool InputComponent::IsKeyDown(const inputs::KeyboardKey i_key)
{
	return m_inputAPI.lock()->IsKeyDown(i_key);
}

bool InputComponent::IsKeyUp(const inputs::KeyboardKey i_key)
{
	return m_inputAPI.lock()->IsKeyUp(i_key);
}

bool InputComponent::IsKeyPressed(const inputs::KeyboardKey i_key)
{
	return m_inputAPI.lock()->IsKeyPressed(i_key);
}

bool InputComponent::IsKeyRelease(const inputs::KeyboardKey i_key)
{
	return m_inputAPI.lock()->IsKeyRelease(i_key);
}

bool InputComponent::IsKeyHold(const inputs::KeyboardKey i_key)
{
	return m_inputAPI.lock()->IsKeyHold(i_key);
}

} // namespace logic