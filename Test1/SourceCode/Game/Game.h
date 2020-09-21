#include "../Constraints.h"
#include "../Graphic/Graphic.h"

#pragma once
class CGame
{
private:
	HWND hWnd = NULL;									// Window handle
	//static CGame* _instance;
	CGraphic* graphic;

	LPDIRECT3DTEXTURE9 brickTexture = NULL;

public:
	//static CGame* GetInstance();

	void Init(HINSTANCE hInstance, int nCmdShow, int width, int height, bool fullscreen);
	void LoadResources();
	void Run();
	void Update(DWORD dt);
	void Render();
	void End();

	~CGame();
};

