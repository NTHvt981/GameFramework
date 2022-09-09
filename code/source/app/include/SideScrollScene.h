#pragma once

#include "Constraints.h"
#include "Scene.h"

#include "Sophia.h"
#include "Jason.h"
#include "JasonTopDown.h"
#include <vector>

#include "SceneRequest.h"
#include "GameRequest.h"

#include "ReadTileSet.h"
#include "TileSet.h"
#include "TileMap.h"

#include "SceneGrid.h"

#include "Portal.h"
#include "TopDownPortal.h"
#include "Wall.h"


#pragma region Enemies
#include "EnemyBuilder.h"
#pragma endregion

#pragma region ITEMS
#include "PickUp.h"
#include "HealthPickUp.h"
#include "EnergyPickUp.h"
#pragma endregion


class CSideScrollScene: public CScene
{
private:
	LPTileSet tileSet;
	std::vector<std::vector<int64_t>> matrix;

	long countId = 0;
	int64_t mode = NORMAL_MODE;
	CArea* currArea = NULL;
	CArea* destArea = NULL;
	CAreaPortal* destPortal = NULL;
	std::map<int64_t, CArea*> areas;
	std::map<int64_t, CAreaPortal*> portals;
	std::list<int64_t> enemiesId;

	//contains all entity, each grid contain a std::list of number, each number is an id
	//of the entity
	std::vector<std::vector<CSceneGrid*>> mapGrid;
	int64_t grid_count_width;
	int64_t grid_count_height;

	CTopDownPortal* topDownPortal;
	CTopDownPortal* endingPortal;

private:
	void LoadLevel();
	void LoadWalls(
		std::vector<std::vector<int64_t>> matrix,
		std::vector<int64_t> solid_tiles,
		int64_t tile_width);
	void LoadBreakableWall();
	void LoadAntiPlayerZones(
		std::vector<std::vector<int64_t>> matrix,
		std::vector<int64_t> anti_player_tiles,
		int64_t tile_width);

	void LoadAreas();
	void LoadPortals();
	void LoadEnemies();
	void DeleteEnemies();

public:
	CSideScrollScene();
	void LoadResources();
	void Start(float x, float y);
	void ReStart(float x, float y);
	void Resume();
	void Update(DWORD dt);
	void Render();
	void End();

	void SetArea(int64_t areaId);

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

	//set new entity pos, add it to entity std::map, set what grid it is in
	void AddEntity(LPEntity entity, float x, float y);
	void RemoveEntity(int64_t id);
	//set what grid is entity in
	void SetEntity(LPEntity entity);
	void ResetEntityCoCollisionBoxes(LPEntity entity, int64_t grid_x, int64_t grid_y);
};

