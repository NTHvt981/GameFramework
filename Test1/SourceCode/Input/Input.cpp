#include "Input.h"

CInput* CInput::__instance = NULL;

CInput* CInput::GetInstance()
{
	if (__instance == NULL) __instance = new CInput();
	return __instance;
}

void CInput::Init(HINSTANCE hInstance, HWND hWnd) {
	HRESULT result;
	result = DirectInput8Create(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		reinterpret_cast<void**>(&dinput),
		NULL
	);

	if (!SUCCEEDED(result))
	{
		LPCTSTR errMsg = GetErrorFromHRESULT(result);
		DebugOut(L"[ERROR] Init Input failed. Error Code: %s\n", errMsg);
		return;
	}

	result = dinput->CreateDevice(GUID_SysKeyboard, &dinputdev, NULL);
	if (!SUCCEEDED(result))
	{
		LPCTSTR errMsg = GetErrorFromHRESULT(result);
		DebugOut(L"[ERROR] Create device failed. Error Code: %s\n", errMsg);
		return;
	}

	result = dinputdev->SetDataFormat(&c_dfDIKeyboard);
	if (!SUCCEEDED(result))
	{
		LPCTSTR errMsg = GetErrorFromHRESULT(result);
		DebugOut(L"[ERROR] set data format. Error Code: %s\n", errMsg);
		return;
	}

	result = dinputdev->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (!SUCCEEDED(result))
	{
		LPCTSTR errMsg = GetErrorFromHRESULT(result);
		DebugOut(L"[ERROR] set cooperative failed. Error Code: %s\n", errMsg);
		return;
	}

	result = dinputdev->Acquire();
	if (!SUCCEEDED(result))
	{
		LPCTSTR errMsg = GetErrorFromHRESULT(result);
		DebugOut(L"[ERROR] Aquire failed. Error Code: %s\n", errMsg);
		return;
	}

	DebugOut(L"[INPUT] Init input Success\n");
}

void CInput::Update()
{
	for (int i = 0; i < sizeof(keys); i++)
	{
		prevKeys[i] = keys[i];
	}
	dinputdev->GetDeviceState(sizeof(keys), (LPVOID)&keys);
}

bool CInput::IsKeyDown(int _key)
{
	return KEYDOWN(keys, _key);
}

bool CInput::IsKeyPressed(int _key)
{
	return (
		KEYDOWN(keys, _key) && (!KEYDOWN(prevKeys, _key))
	);
}

bool CInput::IsKeyRelease(int _key)
{
	return (
		!KEYDOWN(keys, _key) && KEYDOWN(prevKeys, _key)
	);
}

bool CInput::IsKeyHold(int _key)
{
	return (
		KEYDOWN(keys, _key) && KEYDOWN(prevKeys, _key)
		);
}

LPDIRECTINPUT8 CInput::GetInput()
{
	return dinput;
}

LPDIRECTINPUTDEVICE8 CInput::GetDevice()
{
	return dinputdev;
}
