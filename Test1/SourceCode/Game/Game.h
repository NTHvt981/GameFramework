#pragma once
#include <map>

#include "..\Constraints.h"

#include "..\GraphicAndSound\Graphic.h"
#include "..\GraphicAndSound\Audio.h"
#include "..\GraphicAndSound\Sound.h"

#include "..\Library\TextureLibrary.h"
#include "..\Library\SpriteLibrary.h"
#include "..\Debug\Debug.h"

#include "../SceneSystem/SceneManager.h"


#include "../Unit/Pattern.h"

using namespace std;

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

	void Init(HINSTANCE hInstance, int nCmdShow, int width, int height, bool fullscreen);
	void Run();

	~CGame();
};

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight);
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);