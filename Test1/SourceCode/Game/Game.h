#pragma once
#include "..\Constraints.h"
#include "..\Graphic\Graphic.h"
#include "..\Debug\Debug.h"
#include "..\GameObject\GameObject.h"
#include "..\GameObject\HorizontalEntity\HorizontalEntity.h"
#include "..\GameObject\VerticalEntity\VerticalEntity.h"
#include "..\GameObject\PlayableEntity\Player.h"

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

	//vital functions for game object to use
	static void SweptAABB(
		float move_left,		
		float move_top,			
		float move_right,			
		float move_bottom,			
		float move_velocity_x,			
		float move_velocity_y,			
		float static_left,			
		float static_top,
		float static_right,
		float static_bottom,
		float& collide_time,
		float& normal_x,
		float& normal_y);
};

