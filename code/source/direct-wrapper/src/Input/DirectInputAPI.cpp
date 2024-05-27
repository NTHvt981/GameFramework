#include "DirectWrapper/Input/DirectInputAPI.h"
#include "Core/DataTypes/Flag.h"
#include "KeyboardKeyHelper.h"
#include <assert.h>
#include <iostream>
#include "Core/Macros/Macros.h"

namespace direct
{

DirectInputAPI::DirectInputAPI(const HWND i_hwnd, const HINSTANCE i_hInstance)
	: m_hwnd(i_hwnd)
	, m_hInstance(i_hInstance)
{
	ZeroMemory(m_currentKeys, sizeof(m_currentKeys));
	ZeroMemory(m_previousKeys, sizeof(m_previousKeys));
}

DirectInputAPI::~DirectInputAPI()
{
}

void DirectInputAPI::Initialize()
{
	HRESULT result = DirectInput8Create(
		m_hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		&m_directInput,
		NULL
	);
	assert(SUCCEEDED(result));

	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_directInputDevice, NULL);
	assert(SUCCEEDED(result));

	result = m_directInputDevice->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(result));

	result = m_directInputDevice->SetCooperativeLevel(m_hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	assert(SUCCEEDED(result));

	result = m_directInputDevice->Acquire();
	//DEBUG(assert(SUCCEEDED(result)));
}

void DirectInputAPI::UpdateInput()
{
	for (int64_t i = 0; i < sizeof(m_currentKeys); i++)
	{
		m_previousKeys[i] = m_currentKeys[i];
	}

	HRESULT result = m_directInputDevice->GetDeviceState(sizeof(m_currentKeys), (LPVOID)&m_currentKeys);
	//DEBUG(assert(SUCCEEDED(result)));
}

void DirectInputAPI::Shutdown()
{
}

void DirectInputAPI::Pause()
{
	HRESULT result = m_directInputDevice->Unacquire();
	DEBUG(assert(SUCCEEDED(result)));
}

void DirectInputAPI::Resume()
{
	HRESULT result = m_directInputDevice->Acquire();
	DEBUG(assert(SUCCEEDED(result)));
}

bool DirectInputAPI::IsKeyDown(const core::KeyboardKey i_key)
{
	uint64_t index = ToDirectKeyboardKey(i_key);
	return m_currentKeys[index];
}

bool DirectInputAPI::IsKeyUp(const core::KeyboardKey i_key)
{
	return !IsKeyDown(i_key);
}

bool DirectInputAPI::IsKeyPressed(const core::KeyboardKey i_key)
{
	uint64_t index = ToDirectKeyboardKey(i_key);
	return m_currentKeys[index] && (! m_previousKeys[index]);
}

bool DirectInputAPI::IsKeyRelease(const core::KeyboardKey i_key)
{
	uint64_t index = ToDirectKeyboardKey(i_key);
	return (! m_currentKeys[index]) && m_previousKeys[index];
}

bool DirectInputAPI::IsKeyHold(const core::KeyboardKey i_key)
{
	uint64_t index = ToDirectKeyboardKey(i_key);
	return m_currentKeys[index] && m_previousKeys[index];
}

} // namespace direct
