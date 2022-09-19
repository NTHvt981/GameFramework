#include "InputSystem/InputSystem.h"

namespace input
{

////////////////////////////////////////////////////////////////////////////////

InputSystem::InputSystem(std::shared_ptr<INativeInputAPI> i_nativeInputAPI)
	: m_nativeInputAPI(i_nativeInputAPI)
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
	m_nativeInputAPI->ShutDown();
}

////////////////////////////////////////////////////////////////////////////////

} // namespace input