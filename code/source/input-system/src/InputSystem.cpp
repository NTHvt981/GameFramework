#include "InputSystem/InputSystem.h"

namespace input
{

////////////////////////////////////////////////////////////////////////////////

InputSystem::InputSystem(std::unique_ptr<INativeInputAPI> i_nativeInputAPI)
	: m_nativeInputAPI(std::move(i_nativeInputAPI))
{
}

void InputSystem::Initialize()
{
	m_nativeInputAPI->Initialize();
}

void InputSystem::UpdateInput(uint64_t dt)
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

bool InputSystem::IsKeyDown(const KeyboardKey i_key)
{
	return m_nativeInputAPI->IsKeyDown(i_key);
}

bool InputSystem::IsKeyUp(const KeyboardKey i_key)
{
	return m_nativeInputAPI->IsKeyUp(i_key);
}

bool InputSystem::IsKeyPressed(const KeyboardKey i_key)
{
	return m_nativeInputAPI->IsKeyPressed(i_key);
}

bool InputSystem::IsKeyRelease(const KeyboardKey i_key)
{
	return m_nativeInputAPI->IsKeyRelease(i_key);
}

bool InputSystem::IsKeyHold(const KeyboardKey i_key)
{
	return m_nativeInputAPI->IsKeyHold(i_key);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace input