#include "SideScrollScene.h"

void CSideScrollScene::LoadLevel()
{
	int tile_count, tile_width, tile_height, tile_count_width, tile_count_height;
	vector<int> solid_tiles;
	vector<int> anti_player_tiles;

	wstring tileSetDir;

	string tileMatrixDir;
	tileMatrixDir = "Resources/Textfile/TileMaTrix.txt";

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

void CSideScrollScene::LoadWalls(
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

void CSideScrollScene::LoadAntiPlayerZones(
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

void CSideScrollScene::LoadAreas()
{
	areas[1] = new CArea(0, 88, 31, 95);
	areas[2] = new CArea(32, 57, 47, 95);
	areas[3] = new CArea(48, 56, 63, 63);

	areas[4] = new CArea(64, 33, 79, 63);
	areas[5] = new CArea(48, 1, 63, 55);
	areas[6] = new CArea(64, 0, 79, 7);

	areas[7] = new CArea(80, 0, 95, 15);

	for (int i = 1; i <= 7; i++)
	{
		float l = areas[i]->left * 32;
		float t = areas[i]->top * 32;
		float r = areas[i]->right * 32 + 32;
		float b = areas[i]->bottom * 32 + 48;

		areas[i] = new CArea(l, t, r, b);
	}

	areas[8] = new CArea(2048, 256, 2560, 512);
	areas[9] = new CArea(40, 32, 47, 39);

	currArea = areas[1];
}

void CSideScrollScene::LoadPortals()
{
	const int range = 16;
	int ls[range][6] = {
		{ 12, 30, 92, 30, 92, -1 },
		{ 21, 33, 92, 33, 92, 1 },
		{ 23, 46, 60, 46, 60, -1 },
		{ 32, 49, 60, 49, 60, 1 },
		{ 34, 62, 60, 62, 60, -1 },
		{ 43, 65, 60, 65, 60, 1 },

		{ 45, 65, 36, 65, 36, 1},
		{ 54, 62, 36, 62, 36, -1},
		{ 56, 62, 4, 62, 4, -1},
		{ 65, 65, 4, 65, 4, 1},
		{ 67, 78, 4, 78, 4, -1},
		{ 76, 81, 4, 81, 4, 1},

		{ 78, 81, 12, 81, 12, 1},
		{ 87, 78, 12, 78, 12, -1},
		{ 59, 49, 36, 49, 36, 1},
		{ 95, 46, 36, 46, 36, -1}
	};

	for (int i = 0; i < range; i++)
	{
		int id = ls[i][0];
		int areaId = id / 10;
		int reverseId = (id % 10) * 10 + (id / 10);

		int l = ls[i][1] * 32;
		int r = ls[i][3] * 32 + 32;

		int t = ls[i][2] * 32;
		int b = ls[i][4] * 32 + 32;

		int side = ls[i][5];

		portals[id] = new CAreaPortal(l, t, r, b);
		portals[id]->SetTargetId(reverseId);
		portals[id]->SetAreaId(areaId);

		portals[id]->SetDeployDirection(side, 0.5);
	}

	scenePortal = new CTopDownPortal(2112, 432, 2128, 448);
}

void CSideScrollScene::LoadEnemies()
{
	AddEntity(new CJumper(), 400, 2944);
	AddEntity(new CJumper(), 336, 2944);

	AddEntity(new CSkull(), 3*16, 182*16);

	AddEntity(new CDome(), 3 * 16 - 2, 185 * 16 - 2);

	AddEntity(new CFloater(FLOATER_DIAGONAL), 336, 2944);

	AddEntity(new CInsect(), 336, 2944);
	AddEntity(new CWorm(), 400, 2944);

	//AddEntity(new CHealthPickUp(), 400, 2944);
}

CSideScrollScene::CSideScrollScene()
{
	this->mapGrid = DivideSceneGrids(
		SIDESCROLL_LEVEL_SIZE.x, 
		SIDESCROLL_LEVEL_SIZE.y,
		GRID_WIDTH, GRID_HEIGHT, this
	);
	grid_count_width = mapGrid[0].size();
	grid_count_height = mapGrid.size();

	Type = SCENE_TYPES::SideScrollScene;
}

void CSideScrollScene::LoadResources()
{
	LoadLevel();
	LoadAreas();
	LoadPortals();
	LoadEnemies();

	CPlayer* player = CSophia::GetInstance();
	player->SetPosition(INTRO_TO_SIDESCROLL_POS.x, INTRO_TO_SIDESCROLL_POS.y);
	CPlayer::SetCurrentPlayer(player);

	CSophiaFake::GetInstance()->Disable();
}

void CSideScrollScene::Start(float x, float y)
{
	CTileMap::GetInstance()->SetTileSet(tileSet);
	CTileMap::GetInstance()->SetMatrix(matrix);

	CSophia::GetInstance()->SetPosition(x, y);
	CPlayer::SetCurrentPlayer(CSophia::GetInstance());

	CSophiaFake::GetInstance()->Disable();

	for each (pair<int, CArea*> p in areas)
	{
		int areaId = p.first;
		CArea* area = p.second;
		float l, t, r, b;
		area->GetLTRB(l, t, r, b);

		if ((x >= l) && (x < r) && (y >= t) && (y < b))
			SetArea(areaId);
	}
}

void CSideScrollScene::ReStart(float x, float y)
{
	Start(x, y);

	CPlayerHealth::GetInstance()->SetPlayerMode(SOPHIA);

	CSophia::GetInstance()->Enable();
	CJason::GetInstance()->Enable();
}

void CSideScrollScene::Resume()
{
	CTileMap::GetInstance()->SetTileSet(tileSet);
	CTileMap::GetInstance()->SetMatrix(matrix);
}

void CSideScrollScene::Update(DWORD dt)
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

	CCamera *cam = CCamera::GetInstance();
	CPlayer* player = CPlayer::GetCurrentPlayer();
	//check here
}

void CSideScrollScene::Render()
{
	//Render these
	//tiles -> enemies -> player -> portals
	RenderTiles();
	RenderEnemies();

	CSophiaFake::GetInstance()->Render();
	RenderPlayer();

	RenderPortals();

	ExecuteRequests();
}

void CSideScrollScene::End()
{
}

void CSideScrollScene::SetArea(int areaId)
{
	currArea = areas[areaId];
}

void CSideScrollScene::UpdateCamera()
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

void CSideScrollScene::UpdateEnemies(DWORD dt)
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

void CSideScrollScene::UpdatePlayer(DWORD dt)
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

void CSideScrollScene::UpdatePortals(DWORD dt)
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
	CInput* input = CInput::GetInstance();

	bool con1 = scenePortal->IsColliding(CPlayer::GetCurrentPlayer());
	bool con2 = CPlayer::GetCurrentPlayer() == CJason::GetInstance();
	bool con3 = input->IsKeyPressed(DIK_W);

	if (con1 && con2 && con3)
	{
		LPGameRequest request = new CGameRequest(GAME_REQUEST_TYPES::SwitchToTopDown);
		request->sender = SCENE_TYPES::SideScrollScene;

		CGameRequest::AddRequest(request);
	}
}

void CSideScrollScene::RenderTiles()
{
	CTileMap::GetInstance()->Render();
}

void CSideScrollScene::RenderEnemies()
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

void CSideScrollScene::RenderPlayer()
{
	CPlayer::GetCurrentPlayer()->Render();
	CPlayerHealth::GetInstance()->Render();
}

void CSideScrollScene::RenderPortals()
{
	for each (pair<int, CAreaPortal*> por_pair in portals)
	{
		CAreaPortal* portal = por_pair.second;

		portal->Render();
	}

	scenePortal->Render();
}

void CSideScrollScene::ExecuteRequests()
{
	list<LPSceneRequest> requests = CSceneRequest::RequestList;

	while (!requests.empty())
	{
		LPSceneRequest re = requests.front();

		ExecuteRequest(re);
		requests.pop_front();
	}

	CSceneRequest::RequestList.clear();
}

void CSideScrollScene::ExecuteRequest(LPSceneRequest request)
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

	case SCENE_REQUEST_TYPES::SwitchToJason:
		CPlayer::SetCurrentPlayer(CJason::GetInstance());

		CSophiaFake::GetInstance()->Enable();

		CPlayerHealth::GetInstance()->SetPlayerMode(JASON);
		break;

	case SCENE_REQUEST_TYPES::SwitchToSophia:
		CPlayer::SetCurrentPlayer(CSophia::GetInstance());

		CSophiaFake::GetInstance()->Disable();

		CPlayerHealth::GetInstance()->SetPlayerMode(SOPHIA);
		break;

	case SCENE_REQUEST_TYPES::CreateHealthBall:
		AddEntity(new CHealthPickUp(), request->x, request->y);
		break;
		
	default:
		break;
	}
}

void CSideScrollScene::AddEntity(LPEntity entity, float x, float y)
{
	entity->SetPosition(x, y);

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

void CSideScrollScene::RemoveEntity(int id)
{
	LPEntity entity = mapEntities[id];

	int grid_x, grid_y;
	entity->GetGridPosition(grid_x, grid_y);

	mapGrid[grid_y][grid_x]->RemoveEntity(id);

	mapEntities.erase(id);
	free(entity);
}

void CSideScrollScene::SetEntity(LPEntity entity)
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

void CSideScrollScene::ResetEntityCoCollisionBoxes(LPEntity entity, int grid_x, int grid_y)
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

void CSideScrollScene::SetAreaTransition(CAreaPortal* p)
{
	destPortal = portals[p->GetTargetId()];
	int destAreaId = destPortal->GetAreaId();
	destArea = areas[destAreaId];

	mode = BEGIN_CHANGEAREA_MODE;
}

void CSideScrollScene::NormalMode(DWORD dt)
{
	UpdatePlayer(dt);
	UpdateCamera();
	UpdatePortals(dt);
}

void CSideScrollScene::BeginChangeAreaMode(DWORD dt)
{
	CPlayer* player = CPlayer::GetCurrentPlayer();
	CCamera* cam = CCamera::GetInstance();

	player->Disable();
	mode = DURING_CHANGEAREA_MODE;
}

void CSideScrollScene::DuringChangeAreaMode(DWORD dt)
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

void CSideScrollScene::EndChangeAreaMode(DWORD dt)
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
