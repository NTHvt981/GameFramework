#include "TopDownScene.h"

void CTopDownScene::LoadLevel()
{
	int tile_count, tile_width, tile_height, tile_count_width, tile_count_height;
	vector<int> solid_tiles;
	vector<int> anti_player_tiles;

	wstring tileSetDir;

	string tileMatrixDir;
	tileMatrixDir = "Resources/Textfile/TileMaTrixTopDown.txt";

	LoadFileParam(
		tile_count, tile_width, tile_height,
		tile_count_width, tile_count_height,
		solid_tiles, anti_player_tiles,
		matrix, tileSetDir, tileMatrixDir);

	map<int, Box<int>> tileMap;
	GetMap(tile_width, tile_height, tile_count, tileMap);

	tileSet = new CTileSet(
		CGraphic::Instance->LoadTexture(tileSetDir.c_str()),
		tileMap, tile_width
	);

	CTileMap::GetInstance()->SetTileSet(tileSet);
	CTileMap::GetInstance()->SetMatrix(matrix);

	LoadWalls(matrix, solid_tiles, tile_width);
	LoadAntiPlayerZones(matrix, anti_player_tiles, tile_width);
}

void CTopDownScene::LoadWalls(
	vector<vector<int>> matrix, vector<int> solid_tiles, int tile_width)
{
	vector<Box<float>> solid_boxes;
	SetWallPosition(solid_boxes, matrix, solid_tiles, tile_width);
	for each (Box<float> box in solid_boxes)
	{
		AddEntity(
			new CWall(box.left, box.top, box.right, box.bottom),
			box.left + 1, box.top + 1
		);
	}
}

void CTopDownScene::LoadAntiPlayerZones(
	vector<vector<int>> matrix, vector<int> anti_player_tiles, int tile_width)
{
	vector<Box<float>> solid_boxes;
	SetWallPosition(solid_boxes, matrix, anti_player_tiles, tile_width);
	for each (Box<float> box in solid_boxes)
	{
		AddEntity(
			new CAntiPlayer(box.left, box.top, box.right, box.bottom),
			box.left + 1, box.top + 1
		);
	}
}

void CTopDownScene::LoadAreas()
{
	areas[1] = new CArea(0, 56, 7, 63);
	areas[2] = new CArea(8, 56, 15, 63);
	areas[3] = new CArea(16, 56, 23, 63);

	areas[4] = new CArea(16, 48, 23, 55);
	areas[5] = new CArea(16, 40, 23, 47);

	areas[6] = new CArea(8, 40, 15, 47);
	areas[7] = new CArea(8, 32, 15, 39);

	areas[8] = new CArea(0, 32, 7, 39);
	areas[9] = new CArea(0, 24, 7, 31);

	areas[10] = new CArea(8, 24, 15, 31);
	areas[11] = new CArea(16, 24, 23, 31);
	areas[12] = new CArea(24, 24, 31, 31);

	areas[13] = new CArea(24, 16, 31, 23);

	for (int i = 1; i <= 13; i++)
	{
		float l = areas[i]->left * 32;
		float t = areas[i]->top * 32;
		float r = areas[i]->right * 32 + 32;
		float b = areas[i]->bottom * 32 + 48;

		areas[i] = new CArea(l, t, r, b);
	}

	currArea = areas[1];
}

void CTopDownScene::LoadPortals()
{
	const int range = 24;
	int ls[range][5] = {
		{ 102, 7, 60, -1, 0 }, { 201, 9, 60, 1, 0 },

		{ 203, 15, 60, -1, 0 }, { 302, 17, 60, 1, 0 },

		{ 304, 20, 57, 0, 1 }, { 403, 20, 54, 0, -1 },

		{ 405, 20, 49, 0, 1 }, { 504, 20, 46, 0, -1 },

		{ 506, 17, 44, 1, 0 }, { 605, 15, 44, -1, 0 },

		{ 607, 12, 41, 0, 1 }, { 706, 12, 38, 0, -1 },

		{ 708, 9, 36, 1, 0 }, { 807, 7, 36, -1, 0 },

		{ 809, 4, 33, 0, 1 }, { 908, 4, 30, 0, -1 },

		{ 910, 7, 28, -1, 0 }, { 1009, 9, 28, 1, 0 },

		{ 1011, 15, 28, -1, 0 }, { 1110, 17, 28, 1, 0 },

		{ 1112, 23, 28, -1, 0 }, { 1211, 25, 28, 1, 0 },

		{ 1213, 28, 25, 0, 1 }, { 1312, 28, 22, 0, -1 },
	};

	for (int i = 0; i < range; i++)
	{
		int id = ls[i][0];
		int areaId = id / 100;
		int reverseId = (id % 100) * 100 + (id / 100);

		int l = ls[i][1] * 32 - 1;
		int t = ls[i][2] * 32 - 1;

		int r = ls[i][1] * 32 + 1;
		int b = ls[i][2] * 32 + 1;

		int sideX = ls[i][3];
		int sideY = ls[i][4];

		portals[id] = new CAreaPortal(l, t, r, b);
		portals[id]->SetTargetId(reverseId);
		portals[id]->SetAreaId(areaId);

		portals[id]->SetDistance(10);
		portals[id]->SetDeployDirection(sideX, sideY);
	}

	/// <summary>
	/// Scene portal section
	/// </summary>
	sideScrollPortal = new CTopDownPortal(112, 1904, 128, 1920);
	bossPortal = new CTopDownPortal(26 * 32, 18 * 32, 30 * 32, 21 * 32);
}

void CTopDownScene::LoadEnemies()
{
	//AREA 2
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::EyeBall, EYEBALL_TYPE_IDLE), 13 * 32, 58 * 32);
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::EyeBall, EYEBALL_TYPE_MOVE), 10 * 32, 58 * 32);
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::EyeBall, EYEBALL_TYPE_MOVE), 11 * 32, 60 * 32);

	//AREA 3
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::Teleporter), 20 * 32, 59 * 32);
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::Teleporter), 19 * 32, 61 * 32);

	//AREA 4
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::Canon), 17.5 * 32, 51.5 * 32);
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::Canon), 21.5 * 32, 50.5 * 32);

	//AREA 5
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::EyeBall, EYEBALL_TYPE_IDLE), 18 * 32, 42 * 32);
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::EyeBall, EYEBALL_TYPE_MOVE), 20 * 32, 43 * 32);
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::Teleporter), 22 * 32, 42 * 32);

	//AREA 6
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::Spiral), 12 * 32, 43.5 * 32);

	//AREA 7
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::Head), 12 * 32, 34 * 32);
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::Spiral), 12 * 32, 35 * 32);

	//AREA 8
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::Canon), 2 * 32, 34 * 32);
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::EyeBall, EYEBALL_TYPE_IDLE), 2 * 32, 37 * 32);
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::Dasher, DASHER_VERTICAL), 5 * 32, 34 * 32);

	//AREA 9
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::Canon), 2.5 * 32, 28.5 * 32);
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::EyeBall, EYEBALL_TYPE_MOVE), 5 * 32, 26 * 32);

	//AREA 10
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::EyeBall), 10 * 32, 26 * 32);

	//AREA 11
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::EyeBall), 18 * 32, 28 * 32);
	AddEntity(CEnemyBuilder::Create(ENEMY_TYPE::Dasher, DASHER_VERTICAL), 21 * 32, 28 * 32);
}

void CTopDownScene::LoadPickUps()
{
	AddEntity(new CHealthPickUp(), 13 * 32, 28 * 32);
	AddEntity(new CHealthPickUp(), 26.5 * 32, 21.5 * 32);
	AddEntity(new CHealthPickUp(), 29.5 * 32, 21.5 * 32);
}

CTopDownScene::CTopDownScene()
{
	this->mapGrid = DivideSceneGrids(
		TOPDOWN_LEVEL_SIZE.x, 
		TOPDOWN_LEVEL_SIZE.y,
		GRID_WIDTH, GRID_HEIGHT, this
	);
	grid_count_width = mapGrid[0].size();
	grid_count_height = mapGrid.size();

	Type = SCENE_TYPES::TopDownScene;
}

void CTopDownScene::LoadResources()
{
	LoadLevel();
	LoadAreas();
	LoadPortals();
	LoadEnemies();
	LoadPickUps();

	CPlayer* player = CJasonTopDown::GetInstance();
	player->SetPosition(4 * 32, 59 * 32);
	CPlayer::SetCurrentPlayer(player);
}

void CTopDownScene::Start(float x, float y)
{
	CTileMap::GetInstance()->SetTileSet(tileSet);
	CTileMap::GetInstance()->SetMatrix(matrix);

	CJasonTopDown::GetInstance()->SetPosition(x, y);
	CPlayer::SetCurrentPlayer(CJasonTopDown::GetInstance());

	for each (pair<int, CArea*> p in areas)
	{
		int areaId = p.first;
		CArea* area = p.second;
		float l, t, r, b;
		area->GetLTRB(l, t, r, b);

		if ((x >= l) && (x < r) && (y >= t) && (y < b))
			SetArea(areaId);
	}

	CPlayerHealth::GetInstance()->SetPlayerMode(JASON);
}

void CTopDownScene::ReStart(float x, float y)
{
	Start(x, y);
}

void CTopDownScene::Update(DWORD dt)
{
	CSceneRequest::RequestList.clear();
	CInput::GetInstance()->Update();

	UpdateEnemies(dt);

	switch (mode)
	{
	case NORMAL_MODE:
		NormalMode(dt);
		break;

	case BEGIN_CHANGEAREA_MODE:
		BeginChangeAreaMode(dt);
		break;
	case DURING_CHANGEAREA_MODE:
		DuringChangeAreaMode(dt);
		break;
	case END_CHANGEAREA_MODE:
		EndChangeAreaMode(dt);
		break;

	default:
		break;
	}

	CCamera* cam = CCamera::GetInstance();
	CPlayer* player = CPlayer::GetCurrentPlayer();
	//check here
}

void CTopDownScene::Render()
{
	//Render these
	//tiles -> enemies -> player -> portals
	RenderTiles();
	RenderEnemies();

	RenderPlayer();

	RenderPortals();

	ExecuteRequests();
}

void CTopDownScene::End()
{
}

void CTopDownScene::SetArea(int areaId)
{
	currArea = areas[areaId];
}

void CTopDownScene::UpdateCamera()
{
	Vector camPos = CCamera::GetInstance()->GetPosition();
	Vector playerPos = CPlayer::GetCurrentPlayer()->GetPosition();

	CCamera::GetInstance()->SetOuterBound(
		currArea->left,
		currArea->top,
		currArea->right,
		currArea->bottom
	);

	//set camera position
	CCamera::GetInstance()->Follow(
		CPlayer::GetCurrentPlayer()->GetCenter()
	);
}

void CTopDownScene::UpdateEnemies(DWORD dt)
{
	int count = 0;
	float l, t, r, b;
	CCamera::GetInstance()->GetLTRB(l, t, r, b);
	int startX, startY, endX, endY;
	GetGridXandY(startX, startY, endX, endY, l, t, r, b,
		GRID_WIDTH, GRID_HEIGHT, grid_count_width, grid_count_height);

	//update the grid within the camera, these grids call their entities update func
	for (int i = startY; i <= endY; i++)
	{
		for (int j = startX; j <= endX; j++)
		{
			mapGrid[i][j]->Update(dt, count);
		}
	}
}

void CTopDownScene::UpdatePlayer(DWORD dt)
{
	CPlayer* player = CPlayer::GetCurrentPlayer();
	int grid_x = player->GetCenter().x / GRID_WIDTH;
	int grid_y = player->GetCenter().y / GRID_HEIGHT;

	ResetEntityCoCollisionBoxes(
		player,
		grid_x,
		grid_y
	);

	CPlayer::GetCurrentPlayer()->Update(dt);
	CPlayerHealth::GetInstance()->Update(dt);
}

void CTopDownScene::UpdatePortals(DWORD dt)
{
	for each (pair<int, CAreaPortal*> por_pair in portals)
	{
		CAreaPortal* portal = por_pair.second;
		int id = por_pair.first;
		int area1 = portal->GetAreaId();
		int area2 = portal->GetId() % 10;

		portal->Update(dt);
		if (portal->IsCollideWithPlayer())
		{
			SetAreaTransition(portal);
		}
	}

	/// <summary>
	/// Scene portal section
	/// </summary>
	if (sideScrollPortal->IsCollideWithPlayer())
	{
		LPGameRequest request = new CGameRequest(GAME_REQUEST_TYPES::SwitchToSideScroll);
		request->sender = SCENE_TYPES::TopDownScene;

		CGameRequest::AddRequest(request);
	}

	if (bossPortal->IsCollideWithPlayer())
	{
		LPGameRequest request = new CGameRequest(GAME_REQUEST_TYPES::SwitchToBoss);
		request->sender = SCENE_TYPES::TopDownScene;

		CGameRequest::AddRequest(request);

		DebugOut(L"[BOSS] Enter boss Area\n");
	}
}

void CTopDownScene::RenderTiles()
{
	CTileMap::GetInstance()->Render();
}

void CTopDownScene::RenderEnemies()
{
	float l, t, r, b;
	CCamera::GetInstance()->GetLTRB(l, t, r, b);
	int startX, startY, endX, endY;
	GetGridXandY(startX, startY, endX, endY, l, t, r, b,
		GRID_WIDTH, GRID_HEIGHT, grid_count_width, grid_count_height);

	int count = 0;

	for (int i = startY; i <= endY; i++)
	{
		for (int j = startX; j <= endX; j++)
		{
			mapGrid[i][j]->Render();
		}
	}
}

void CTopDownScene::RenderPlayer()
{
	CPlayer::GetCurrentPlayer()->Render();
	CPlayerHealth::GetInstance()->Render();
}

void CTopDownScene::RenderPortals()
{
	for each (pair<int, CAreaPortal*> por_pair in portals)
	{
		CAreaPortal* portal = por_pair.second;

		portal->Render();
	}

	/// <summary>
	/// Scene portal section
	/// </summary>
	sideScrollPortal->Render();

	bossPortal->Render();
}

void CTopDownScene::ExecuteRequests()
{
	list<LPSceneRequest> requests = CSceneRequest::RequestList;

	while (!requests.empty())
	{
		LPSceneRequest re = requests.front();

		ExecuteRequest(re);
		requests.pop_front();
	}
}

void CTopDownScene::ExecuteRequest(LPSceneRequest request)
{
	switch (request->Type)
	{
	case SCENE_REQUEST_TYPES::CreateEntity:
		AddEntity(
			request->entity,
			request->x,
			request->y
		);
		break;
	case SCENE_REQUEST_TYPES::DeleteEntity:
		RemoveEntity(request->id);
		break;
	case SCENE_REQUEST_TYPES::SetEntity:
		SetEntity(request->entity);
		break;

	case SCENE_REQUEST_TYPES::CreateHealthBall:
		AddEntity(new CHealthPickUp(), request->x, request->y);
		break;
	default:
		break;
	}
}

void CTopDownScene::AddEntity(LPEntity entity, float x, float y)
{
	entity->SetCenter(x, y);

	entity->SetId(countId);
	mapEntities[countId] = entity;
	countId++;

	if (entity->GetType() == GOTYPES::PlayerBullet)
	{
		int i = 0;
		i++;
	}

	SetEntity(entity);
}

void CTopDownScene::RemoveEntity(int id)
{
	LPEntity entity = mapEntities[id];

	int grid_x, grid_y;
	entity->GetGridPosition(grid_x, grid_y);

	mapGrid[grid_y][grid_x]->RemoveEntity(id);

	mapEntities.erase(id);
	free(entity);
}

void CTopDownScene::SetEntity(LPEntity entity)
{
	if (entity == NULL) return;
	if (entity->GetId() < 0 || entity->GetId() > countId) return;

	int old_grid_x, old_grid_y;
	entity->GetGridPosition(old_grid_x, old_grid_y);
	if (!(old_grid_x < 0 || old_grid_y < 0 ||
		old_grid_x >= grid_count_width || old_grid_y >= grid_count_height))
	{
		mapGrid[old_grid_y][old_grid_x]->RemoveEntity(entity->GetId());
	}

	int grid_x = entity->GetCenter().x / GRID_WIDTH;
	int grid_y = entity->GetCenter().y / GRID_HEIGHT;

	//assert code
	if (grid_x < 0 || grid_y < 0 ||
		grid_x >= grid_count_width || grid_y >= grid_count_height)
	{
		DebugOut(L"[ERROR] vector size violation at side scroll scene ccp set entity\n");
		return;
	}

	mapGrid[grid_y][grid_x]->AddEntity(entity->GetId());
	entity->SetGridPosition(grid_x, grid_y);

	//for debug
	ResetEntityCoCollisionBoxes(entity, grid_x, grid_y);
}

void CTopDownScene::ResetEntityCoCollisionBoxes(LPEntity entity, int grid_x, int grid_y)
{
	list<LPCollisionBox> newCoCollisionBoxes;
	list<CSceneGrid*> selfAndSuroundGrids;
	selfAndSuroundGrids.push_back(mapGrid[grid_y][grid_x]);
	if (grid_x > 0)
		selfAndSuroundGrids.push_back(mapGrid[grid_y][grid_x - 1]);
	if (grid_x < grid_count_width - 1)
		selfAndSuroundGrids.push_back(mapGrid[grid_y][grid_x + 1]);

	if (grid_y > 0)
		selfAndSuroundGrids.push_back(mapGrid[grid_y - 1][grid_x]);
	if (grid_y < grid_count_height - 1)
		selfAndSuroundGrids.push_back(mapGrid[grid_y + 1][grid_x]);

	if (grid_x > 0 && grid_y > 0)
		selfAndSuroundGrids.push_back(mapGrid[grid_y - 1][grid_x - 1]);
	if (grid_x > 0 && grid_y < grid_count_height - 1)
		selfAndSuroundGrids.push_back(mapGrid[grid_y + 1][grid_x - 1]);
	if (grid_x < grid_count_width - 1 && grid_y < grid_count_height - 1)
		selfAndSuroundGrids.push_back(mapGrid[grid_y + 1][grid_x + 1]);
	if (grid_x < grid_count_width - 1 && grid_y > 0)
		selfAndSuroundGrids.push_back(mapGrid[grid_y - 1][grid_x + 1]);

	for each (CSceneGrid * grid in selfAndSuroundGrids)
	{
		for each (int id in grid->GetColBoxes())
			newCoCollisionBoxes.push_back(
				CCollision::GetInstance()->GetCollisionBox(id)
			);
	}

	entity->GetCollisionBox()->ResetCoCollisionBoxes(newCoCollisionBoxes);
}

void CTopDownScene::SetAreaTransition(CAreaPortal* p)
{
	destPortal = portals[p->GetTargetId()];
	int destAreaId = destPortal->GetAreaId();
	destArea = areas[destAreaId];

	mode = BEGIN_CHANGEAREA_MODE;
}

void CTopDownScene::NormalMode(DWORD dt)
{
	UpdatePlayer(dt);
	UpdateCamera();
	UpdatePortals(dt);
}

void CTopDownScene::BeginChangeAreaMode(DWORD dt)
{
	CPlayer* player = CPlayer::GetCurrentPlayer();
	CCamera* cam = CCamera::GetInstance();

	player->Disable();
	mode = DURING_CHANGEAREA_MODE;
}

void CTopDownScene::DuringChangeAreaMode(DWORD dt)
{
	CPlayer* player = CPlayer::GetCurrentPlayer();
	CCamera* cam = CCamera::GetInstance();

	float cam_l, cam_t, cam_r, cam_b;
	float area_l, area_t, area_r, area_b;

	destArea->GetLTRB(area_l, area_t, area_r, area_b);
	cam->GetLTRB(cam_l, cam_t, cam_r, cam_b);

	float dx = max(max(0, area_l - cam_l), cam_r - area_r);
	float dy = max(max(0, area_t - cam_t), cam_b - area_b);
	// if area_l - cam_r > 0
	// then destination area is to the right of camera
	int sidex = (area_l - cam_l) > 0 ? 1 : -1;
	int sidey = (area_t - cam_t) > 0 ? 1 : -1;

	if (dx == 0 && dy == 0)
	{
		mode = END_CHANGEAREA_MODE;
	}
	else
	{
		cam->Move(min(6, dx) * sidex, min(6, dy) * sidey);
	}
}

void CTopDownScene::EndChangeAreaMode(DWORD dt)
{
	CPlayer* player = CPlayer::GetCurrentPlayer();
	CCamera* cam = CCamera::GetInstance();

	currArea = destArea;
	destPortal->SetIsCollideWithPlayer(true);
	player->Enable();
	mode = NORMAL_MODE;

	float x, y;
	destPortal->GetDeployPosition(x, y);
	player->SetCenter(
		x,
		y
	);

	mode = NORMAL_MODE;
}
