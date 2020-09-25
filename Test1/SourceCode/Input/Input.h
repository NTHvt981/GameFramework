#pragma once

#include "..\Constraints.h"
#include <dinput.h>

//input define
#define KEYDOWN(name, key) (name[key] & 0x80)
#define KEYUP(name, key) (name[key] & 0x80)

class CInput
{
private:
	static CInput* __instance;
	LPDIRECTINPUT8 dinput;
	LPDIRECTINPUTDEVICE8 dinputdev;

	char keys[256];
	char prevKeys[256];
public:
	static CInput* GetInstance();
	void Init(HINSTANCE hInstance, HWND hWnd);
	void Update();

	bool IsKeyDown(int key);
	bool IsKeyPressed(int key);
	bool IsKeyRelease(int key);
	bool IsKeyHold(int key);

	LPDIRECTINPUT8 GetInput();
	LPDIRECTINPUTDEVICE8 GetDevice();
};

