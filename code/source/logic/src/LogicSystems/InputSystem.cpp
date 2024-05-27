#include "Logic/LogicSystems/InputSystem.h"

namespace logic
{

////////////////////////////////////////////////////////////////////////////////

InputSystem::InputSystem(std::unique_ptr<core::INativeInputAPI> i_nativeInputAPI)
	: m_nativeInputAPI(std::move(i_nativeInputAPI))
{
}

void InputSystem::Initialize()
{
	m_nativeInputAPI->Initialize();
}

void InputSystem::UpdateInput(const core::Duration& dt)
{
	m_nativeInputAPI->UpdateInput();
}

void InputSystem::Pause()
{
	m_nativeInputAPI->Pause();
}

void InputSystem::Resume()
{
	m_nativeInputAPI->Resume();
}

void InputSystem::Shutdown()
{
	m_nativeInputAPI->Shutdown();
}

bool InputSystem::IsKeyDown(const core::KeyboardKey i_key) const
{
	return m_nativeInputAPI->IsKeyDown(i_key);
}

bool InputSystem::IsKeyUp(const core::KeyboardKey i_key) const
{
	return m_nativeInputAPI->IsKeyUp(i_key);
}

bool InputSystem::IsKeyPressed(const core::KeyboardKey i_key) const
{
	return m_nativeInputAPI->IsKeyPressed(i_key);
}

bool InputSystem::IsKeyRelease(const core::KeyboardKey i_key) const
{
	return m_nativeInputAPI->IsKeyRelease(i_key);
}

bool InputSystem::IsKeyHold(const core::KeyboardKey i_key) const
{
	return m_nativeInputAPI->IsKeyHold(i_key);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace logic