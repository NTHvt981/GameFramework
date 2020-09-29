#include "Debug.h"
#include <comdef.h>

void DebugOut(wchar_t* fmt, ...)
{
	wchar_t s[4096];
	VA_PRINTS(s);
	OutputDebugString(s);
}

void DebugOutTitle(wchar_t* fmt, ...)
{
	wchar_t s[1024];
	VA_PRINTS(s);
	//SetWindowText(hWnd, s);
}

LPCTSTR GetErrorFromHRESULT(HRESULT result) 
{
	_com_error err(result);
	LPCTSTR errMsg = err.ErrorMessage();
	return errMsg;
}

void DebugKeyPress(int key)
{
	if (CInput::GetInstance()->IsKeyPressed(key))
		DebugOut(L"[INFO-KEY] Press key %d\n", key);
}

void DebugKeyHold(int key)
{
	if (CInput::GetInstance()->IsKeyHold(key))
		DebugOut(L"[INFO-KEY] Hold key %d\n", key);
}

void DebugKeyRelease(int key)
{
	if (CInput::GetInstance()->IsKeyRelease(key))
		DebugOut(L"[INFO-KEY] Release key %d\n", key);
}

void DebugKeyDown(int key)
{
	if (CInput::GetInstance()->IsKeyDown(key))
		DebugOut(L"[INFO-KEY] Hold key %d\n", key);
}
