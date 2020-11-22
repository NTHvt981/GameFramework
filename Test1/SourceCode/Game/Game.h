#pragma once
#include <map>
#include "..\Constraints.h"
#include "..\Graphic\Graphic.h"
#include "GameRequest.h"

#include "..\Library\TextureLibrary.h"
#include "..\Library\SpriteLibrary.h"
#include "..\Library\AnimationLibrary.h"
#include "..\Debug\Debug.h"

#include "..\GameObject\GameObject.h"
#include "..\Player\Player.h"
#include "..\GameObject\StaticObjects\AntiPlayer.h"
#include "..\GameObject\Enemies\Worm.h"
#include "..\GameObject\Enemies\Dome.h"
#include "..\GameObject\Enemies\Jumper.h"
#include "..\GameObject\Enemies\Orb.h"
#include "..\GameObject\Enemies\Walker.h"

#include "..\GameObject\StaticObjects\Wall.h"

#include "../FileAndString/ReadTileSet.h"
#include "../FileAndString/StringHelper.h"

#include "../TileSystem/TileMap.h"
#include "../TileSystem/TileSet.h"

#include "../GridSystem/Grid.h"
#include "../AreaAndScene/Area.h"
#include "../GameObject/StaticObjects/Portal.h"

#define NORMAL_MODE 0
#define CHANGEAREA_MODE 1
#define CHANGESCENE_MODE 2
#define CUTSCENE_MODE 3

#define INTRO_SCENE 0
#define SIDESCROLL_SCENE 1
#define TOPDOWN_SCENE 2

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
	long countId = 0;

	//this vars for player changing scene
	int mode = NORMAL_MODE;
	CArea* currArea = NULL;
	CArea* destArea = NULL;
	CPortal* destPortal = NULL;
	map<int, CArea*> areas;
	map<int, CPortal*> portals;

	list<LPRequest> requestList;

private:
	static CGame* __instance;
private:
	void LoadResources();
	void LoadTextures();
	void LoadSprites();
	void LoadLevel();
	void LoadWalls(
		vector<vector<int>> matrix,
		vector<int> solid_tiles,
		int tile_width);

	void LoadAntiPlayerZones(
		vector<vector<int>> matrix,
		vector<int> anti_player_tiles,
		int tile_width);

	void LoadAreas();
	void LoadPortals();
	void LoadEnemies();

	void Update(DWORD dt);
	void UpdateCamera();
	void UpdateCollisionBoxes(DWORD dt);
	void UpdateEnemies(DWORD dt);
	void UpdatePlayer(DWORD dt);
	void UpdatePortals(DWORD dt);

	void SetAreaTransition(CPortal* p);
	void NormalMode(DWORD dt);
	void TransitionMode(DWORD dt);

	void Render();

	void RenderTiles();
	void RenderEnemies();
	void RenderPlayer();
	void RenderPortals();

	void CleanResources();
public:
	static CGame* GetInstance();

	void Init(HINSTANCE hInstance, int nCmdShow, int width, int height, bool fullscreen);
	void Run();

	~CGame();

	void AddGameObject(LPGameObject gameObject);

	void ResetEntityCoCollisionBoxes(LPEntity entity, int grid_x, int grid_y);

	LPEntity GetEntity(int id);

	void AddRequest(LPRequest re);

private:
	void ExecuteRequests(list<LPRequest> requests);
	void ExecuteRequest(LPRequest request);

	//set new entity pos, add it to entity map, set what grid it is in
	void AddEntity(LPEntity entity, float x, float y);
	void RemoveEntity(int id);
	//set what grid is entity in
	void SetEntity(LPEntity entity);
};

void GetGridXandY(
	int &startX, int &startY, int& endX, int& endY,
	float left, float top, float right, float bottom, 
	float gridWidth, float gridHeight,
	int grid_count_width, int grid_count_height);