#include "InputDirectx/DirectxInputAPI.h"
#include "Core/DataTypes/Flag.h"
#include "KeyboardKeyHelper.h"
#include <assert.h>
#include <iostream>

namespace input
{

core::Flag s_initFlag;
core::Flag s_shutdownFlag;

DirectxInputAPI::DirectxInputAPI(const HWND i_hwnd, const HINSTANCE i_hInstance)
	: m_hwnd(i_hwnd)
	, m_hInstance(i_hInstance)
{
}

DirectxInputAPI::~DirectxInputAPI()
{
}

void DirectxInputAPI::Initialize()
{
	HRESULT result = DirectInput8Create(
		m_hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		reinterpret_cast<void**>(&m_directInput),
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
	assert(SUCCEEDED(result));
}

void DirectxInputAPI::UpdateInput()
{
	for (int64_t i = 0; i < sizeof(m_currentKeys); i++)
	{
		m_previousKeys[i] = m_currentKeys[i];
	}

	HRESULT result = m_directInputDevice->GetDeviceState(sizeof(m_currentKeys), (LPVOID)&m_currentKeys);
	assert(SUCCEEDED(result));
}

void DirectxInputAPI::ShutDown()
{
}

void DirectxInputAPI::Pause()
{
	HRESULT result = m_directInputDevice->Unacquire();
	assert(SUCCEEDED(result));
}

void DirectxInputAPI::Resume()
{
	HRESULT result = m_directInputDevice->Acquire();
	assert(SUCCEEDED(result));
}

bool DirectxInputAPI::IsKeyDown(const KeyboardKey i_key)
{
	uint64_t index = ToDirectKeyboardKey(i_key);
	return m_currentKeys[index];
}

bool DirectxInputAPI::IsKeyUp(const KeyboardKey i_key)
{
	return !IsKeyDown(i_key);
}

bool DirectxInputAPI::IsKeyPressed(const KeyboardKey i_key)
{
	uint64_t index = ToDirectKeyboardKey(i_key);
	return m_currentKeys[index] && (! m_previousKeys[index]);
}

bool DirectxInputAPI::IsKeyRelease(const KeyboardKey i_key)
{
	uint64_t index = ToDirectKeyboardKey(i_key);
	return (! m_currentKeys[index]) && m_previousKeys[index];
}

bool DirectxInputAPI::IsKeyHold(const KeyboardKey i_key)
{
	uint64_t index = ToDirectKeyboardKey(i_key);
	return m_currentKeys[index] && m_previousKeys[index];
}

} // namespace input
