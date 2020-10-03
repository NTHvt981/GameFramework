#pragma once
#include "..\Constraints.h"
#include "..\Graphic\Graphic.h"
#include "..\Library\TextureLibrary.h"
#include "..\Library\SpriteLibrary.h"
#include "..\Library\AnimationLibrary.h"
#include "..\Debug\Debug.h"
#include "..\GameObject\GameObject.h"
#include "..\GameObject\HorizontalEntity\HorizontalEntity.h"
#include "..\GameObject\VerticalEntity\VerticalEntity.h"
#include "..\GameObject\PlayableEntity\Player.h"
#include "..\GameObject\StaticObjects\Wall.h"
#include "..\GameObject\StaticObjects\Ground.h"

using namespace std;

class CGame
{
private:
	HWND hWnd = NULL;									// Window handle

	vector<LPGameObject> lGameObjects;
private:
	static CGame* __instance;
private:
	void LoadResources();
	void LoadTextures();
	void LoadSprites();
	void LoadAnimations();
	void Update(DWORD dt);
	void Render();
	void CleanResources();
public:
	static CGame* GetInstance();

	void Init(HINSTANCE hInstance, int nCmdShow, int width, int height, bool fullscreen);
	void Run();

	~CGame();

	void AddGameObject(LPGameObject gameObject);
	void AddEntity(LPEntity entity, float x, float y);
};

