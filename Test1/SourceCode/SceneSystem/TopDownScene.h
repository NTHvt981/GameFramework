#pragma once

#include "../Constraints.h"
#include "Scene.h"

#include "../Player/JasonTopDown.h"
#include <vector>

#include "../SceneSystem/SceneRequest.h"
#include "../Game/GameRequest.h"

#include "../FileAndString/ReadTileSet.h"
#include "../TileSystem/TileSet.h"
#include "../TileSystem/TileMap.h"

#include "../GridSystem/SceneGrid.h"

#include "../GameObject/StaticObjects/Portal.h"
#include "../GameObject/StaticObjects/TopDownPortal.h"
#include "../GameObject/StaticObjects/Wall.h"

#pragma region ENEMIES
#include "../GameObject/Enemies/EnemyBuilder.h"
#pragma endregion

#pragma region ITEMS
#include "../PlayerItems/PickUp.h"
#include "../PlayerItems/HealthPickUp.h"
#include "../PlayerItems/EnergyPickUp.h"
#include "../PlayerItems/PowerPickUp.h"
#pragma endregion

class CTopDownScene : public CScene
{
private:
	LPTileSet tileSet;
	vector<vector<int>> matrix;

	long countId = 0;
	int mode = NORMAL_MODE;
	CArea* currArea = NULL;
	CArea* destArea = NULL;
	CAreaPortal* destPortal = NULL;
	map<int, CArea*> areas;
	map<int, CAreaPortal*> portals;

	CTopDownPortal* sideScrollPortal;

	CTopDownPortal* bossPortal;

	//contains all entity, each grid contain a list of number, each number is an id
	//of the entity
	vector<vector<CSceneGrid*>> mapGrid;
	int grid_count_width;
	int grid_count_height;

private:
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
	void LoadPickUps();

public:
	CTopDownScene();
	void LoadResources();
	void Start(float x, float y);
	void ReStart(float x, float y);
	void Update(DWORD dt);
	void Render();
	void End();

	void SetArea(int areaId);

private:
	/// <summary>
	/// Update functions
	/// </summary>
	void UpdateCamera();
	void UpdateEnemies(DWORD dt);
	void UpdatePlayer(DWORD dt);
	void UpdatePortals(DWORD dt);

private:
	/// <summary>
	/// Render functions
	/// </summary>
	void RenderTiles();
	void RenderEnemies();
	void RenderPlayer();
	void RenderPortals();

private:
	void SetAreaTransition(CAreaPortal* p);
	void NormalMode(DWORD dt);

	void BeginChangeAreaMode(DWORD dt);
	void DuringChangeAreaMode(DWORD dt);
	void EndChangeAreaMode(DWORD dt);

private:
	void ExecuteRequests();
	void ExecuteRequest(LPSceneRequest request);

	//set new entity pos, add it to entity map, set what grid it is in
	void AddEntity(LPEntity entity, float x, float y);
	void RemoveEntity(int id);
	//set what grid is entity in
	void SetEntity(LPEntity entity);
	void ResetEntityCoCollisionBoxes(LPEntity entity, int grid_x, int grid_y);
};

