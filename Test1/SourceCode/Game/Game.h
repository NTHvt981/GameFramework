#pragma once
#include <map>
#include "..\Constraints.h"
#include "..\Graphic\Graphic.h"

#include "..\Library\TextureLibrary.h"
#include "..\Library\SpriteLibrary.h"
#include "..\Library\AnimationLibrary.h"
#include "..\Debug\Debug.h"

#include "..\GameObject\GameObject.h"
#include "..\GameObject\DynamicObjects\HorizontalEntity.h"
#include "..\GameObject\DynamicObjects\VerticalEntity.h"
#include "..\GameObject\DynamicObjects\Player.h"
#include "..\GameObject\DynamicObjects\Enemies\Worm.h"
#include "..\GameObject\DynamicObjects\Enemies\Dome.h"
#include "..\GameObject\DynamicObjects\Enemies\Jumper.h"
#include "..\GameObject\DynamicObjects\Enemies\Orb.h"
#include "..\GameObject\DynamicObjects\Enemies\Walker.h"

#include "..\GameObject\StaticObjects\Wall.h"
#include "..\GameObject\StaticObjects\Ground.h"

#include "../FileAndString/ReadTileSet.h"
#include "../FileAndString/StringHelper.h"

#include "../TileSystem/TileMap.h"
#include "../TileSystem/TileSet.h"

#include "../GridSystem/Grid.h"

using namespace std;

class CGame
{
private:
	HWND hWnd = NULL;									// Window handle

	//contains all game object that always get update, render (including player)
	vector<LPGameObject> lGameObjects;

	//contains all entity, each grid contain a list of number, each number is an id
	//of the entity
	map<int, LPEntity> mapEntities = map<int, LPEntity>();
	vector<vector<CGrid>> mapGrid;
	int grid_count_width;
	int grid_count_height;

	//this var for debug
	int countId = 0;
private:
	static CGame* __instance;
private:
	void LoadResources();
	void LoadTextures();
	void LoadSprites();
	void LoadAnimations();
	void LoadLevel();
	void Update(DWORD dt);
	void Render();
	void CleanResources();
public:
	static CGame* GetInstance();

	void Init(HINSTANCE hInstance, int nCmdShow, int width, int height, bool fullscreen);
	void Run();

	~CGame();

	void AddGameObject(LPGameObject gameObject);

	//set new entity pos, add it to entity map, set what grid it is in
	void AddEntity(LPEntity entity, float x, float y);
	//set what grid is entity in
	void SetEntity(LPEntity entity);

	LPEntity GetEntity(int id);
};

void GetGridXandY(int &startX, int &startY, int& endX, int& endY,
	float left, float top, float right, float bottom, 
	float gridWidth, float gridHeight,
	int grid_count_width, int grid_count_height);