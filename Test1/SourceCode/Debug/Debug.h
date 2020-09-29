#pragma once
#include "../Constraints.h"
#include "../Input/Input.h"

// DEBUG SUPPORT FUNCTIONS //////////////

#define _W(x)  __W(x)
#define __W(x)  L##x

#define VA_PRINTS(s) {				\
		va_list argp;				\
		va_start(argp, fmt);		\
		vswprintf_s(s, fmt, argp);	\
		va_end(argp);				\
}

void DebugOut(wchar_t* fmt, ...);
void DebugOutTitle(wchar_t* fmt, ...);
LPCTSTR GetErrorFromHRESULT(HRESULT result);

void DebugKeyPress(int key);
void DebugKeyHold(int key);
void DebugKeyRelease(int key);
void DebugKeyDown(int key);
