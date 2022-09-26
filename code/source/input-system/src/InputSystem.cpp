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

////////////////////////////////////////////////////////////////////////////////

} // namespace input