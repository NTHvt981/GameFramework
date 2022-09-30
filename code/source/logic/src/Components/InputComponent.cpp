#include "Logic/Components/InputComponent.h"

namespace logic
{

InputComponent::InputComponent(std::weak_ptr<input::IInputAPI> i_inputAPI)
	: m_inputAPI(i_inputAPI)
{
}

bool InputComponent::IsKeyDown(const input::KeyboardKey i_key)
{
	return m_inputAPI.lock()->IsKeyDown(i_key);
}

bool InputComponent::IsKeyUp(const input::KeyboardKey i_key)
{
	return m_inputAPI.lock()->IsKeyUp(i_key);
}

bool InputComponent::IsKeyPressed(const input::KeyboardKey i_key)
{
	return m_inputAPI.lock()->IsKeyPressed(i_key);
}

bool InputComponent::IsKeyRelease(const input::KeyboardKey i_key)
{
	return m_inputAPI.lock()->IsKeyRelease(i_key);
}

bool InputComponent::IsKeyHold(const input::KeyboardKey i_key)
{
	return m_inputAPI.lock()->IsKeyHold(i_key);
}

} // namespace logic