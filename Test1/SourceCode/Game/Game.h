#pragma once
#include "..\Constraints.h"
#include "..\Graphic\Graphic.h"
#include "..\Debug\Debug.h"
#include "..\GameObject\GameObject.h"
#include "..\GameObject\HorizontalEntity\HorizontalEntity.h"
#include "..\GameObject\VerticalEntity\VerticalEntity.h"

using namespace std;

class CGame
{
private:
	HWND hWnd = NULL;									// Window handle

	//temp game object
	CGameObject* lHorizontalEntity;

	vector<LPGameObject> lGameObjects;
private:
	static CGame* __instance;
private:
	void LoadResources();
	void Update(DWORD dt);
	void Render();
	void CleanResources();
public:
	static CGame* GetInstance();

	void Init(HINSTANCE hInstance, int nCmdShow, int width, int height, bool fullscreen);
	void Run();

	~CGame();
};

