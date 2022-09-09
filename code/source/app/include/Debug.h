#pragma once
#include "Constraints.h"
#include "Input.h"

// DEBUG SUPPORT FUNCTIONS //////////////

#define _W(x)  __W(x)
#define __W(x)  L##x

#define VA_PRINTS(s) {				\
		va_list argp;				\
		va_start(argp, fmt);		\
		vswprintf_s(s, fmt, argp);	\
		va_end(argp);				\
}

void DebugOut(const wchar_t* fmt, ...);
void DebugOutTitle(const wchar_t* fmt, ...);
LPCTSTR GetErrorFromHRESULT(HRESULT result);

void DebugKeyPress(int64_t key);
void DebugKeyHold(int64_t key);
void DebugKeyRelease(int64_t key);
void DebugKeyDown(int64_t key);
