#pragma once
#include "..\Constraints.h"
#include "..\Graphic\Graphic.h"
#include "..\Debug\Debug.h"
#include "..\GameObject\GameObject.h"
#include "..\GameObject\HorizontalEntity\HorizontalEntity.h"

using namespace std;

class CGame
{
private:
	HWND hWnd = NULL;									// Window handle

	//temp game object
	CGameObject* lHorizontalEntity;
public:
	static CGame* Instance;
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

