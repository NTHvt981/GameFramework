#pragma once
#include <map>

#include "Constraints.h"

#include "Graphic.h"
#include "Audio.h"
#include "Sound.h"

#include "TextureLibrary.h"
#include "SpriteLibrary.h"
#include "Debug.h"

#include "SceneManager.h"


#include "Pattern.h"



class CGame
{
private:
	HWND hWnd = NULL;									// Window handle
	CSceneManager manager;

private:
	static CGame* __instance;
private:
	void LoadResources();
	void LoadTextures();
	void LoadSprites();

	void Update(DWORD dt);

	void Render();

	void CleanResources();
public:
	static CGame* GetInstance();

	void Init(HINSTANCE hInstance, int64_t nCmdShow, int64_t width, int64_t height, bool fullscreen);
	void Run();

	~CGame();
};

HWND CreateGameWindow(HINSTANCE hInstance, int64_t nCmdShow, int64_t ScreenWidth, int64_t ScreenHeight);
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);