#include "Game.h"

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight);
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

CGame* CGame::__instance = NULL;

CGame* CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}

void CGame::Init(HINSTANCE hInstance, int nCmdShow, int width, int height, bool fullscreen)
{
	hWnd = CreateGameWindow(hInstance, nCmdShow, width, height);
	CGraphic::Instance->Init(hWnd);

	CInput::GetInstance()->Init(hInstance, hWnd);
	
	mapGrid = DivideGrids(GAME_WIDTH, GAME_HEIGHT, GRID_WIDTH, GRID_HEIGHT);
	grid_count_width = mapGrid[0].size();
	grid_count_height = mapGrid.size();
}

void CGame::LoadResources()
{
	LoadTextures();
	LoadSprites();
	LoadLevel();
	LoadAreas();
	LoadPortals();
	LoadEnemies();

	CPlayer* player = new CPlayer();
	player->SetPosition(200, 92*32);
	AddGameObject(player);
	CPlayer::SetCurrentPlayer(player);
}

void CGame::LoadTextures()
{
	//CTextureLibrary::GetInstance()->Add(CAR_TEXTURE, L"Resources/Texture/My car spritesheet.png");
	CTextureLibrary::GetInstance()->Add(PLAYER_TEXTURE, PLAYER_TEXTURE_PATH);
	CTextureLibrary::GetInstance()->Add(ENEMIES_TEXTURE, ENEMIES_TEXTURE_PATH);
	CTextureLibrary::GetInstance()->Add(PLAYER_HEALTH_TEXTURE, PLAYER_HEALTH_TEXTURE_PATH);
	CTextureLibrary::GetInstance()
		->Add(ID_TEX_BBOX, TEX_BBOX_PATH);
}

void CGame::LoadSprites()
{
	LPDIRECT3DTEXTURE9 textPlayer = CTextureLibrary::GetInstance()->Get(PLAYER_TEXTURE);
	LPDIRECT3DTEXTURE9 textEnemies = CTextureLibrary::GetInstance()->Get(ENEMIES_TEXTURE);
	LPDIRECT3DTEXTURE9 textPlayerHealth = CTextureLibrary::GetInstance()->Get(PLAYER_HEALTH_TEXTURE);
	CSpriteLibrary* lib = CSpriteLibrary::GetInstance();

	// CAR
	lib->Add(ID_CAR_GUN_LEFT, 11, 4, 18, 8, textPlayer);
	lib->Add(ID_CAR_GUN_RIGHT, 12, 13, 19, 17, textPlayer);
	lib->Add(ID_CAR_GUN_UPLEFT, 20, 2, 28, 10, textPlayer);
	lib->Add(ID_CAR_GUN_UPRIGHT, 20, 11, 28, 19, textPlayer);
	lib->Add(ID_CAR_GUN_UP, 31, 2, 35, 9, textPlayer);

	lib->Add(ID_CAR_HEAD_LEFT, 2,	20,	18,	28, textPlayer);
	lib->Add(ID_CAR_HEAD_RIGHT, 2,	29,	18,	37, textPlayer);
	lib->Add(ID_CAR_HEAD_UPLEFT, 56,	21,	56+16,	36, textPlayer);
	lib->Add(ID_CAR_HEAD_UPRIGHT, 38,	21,	38+16,	35, textPlayer);

	lib->Add(ID_CAR_BODY, 109,	2,	115,	9, textPlayer);
	lib->Add(ID_CAR_BODY_UPRIGHT, 135, 2, 143, 10, textPlayer);
	lib->Add(ID_CAR_BODY_UPLEFT, 126, 2, 134, 10, textPlayer);

	lib->Add(ID_CAR_WHEEL_1, 38, 11, 45, 19, textPlayer);
	lib->Add(ID_CAR_WHEEL_2, 47, 11, 54, 19, textPlayer);
	lib->Add(ID_CAR_WHEEL_3, 56, 11, 63, 19, textPlayer);
	lib->Add(ID_CAR_WHEEL_4, 65, 11, 72, 19, textPlayer);
	lib->Add(ID_CAR_WHEEL_5, 38, 2, 45, 10, textPlayer);
	lib->Add(ID_CAR_WHEEL_6, 47, 2, 54, 10, textPlayer);
	lib->Add(ID_CAR_WHEEL_7, 56, 2, 63, 10, textPlayer);
	lib->Add(ID_CAR_WHEEL_8, 65, 2, 72, 10, textPlayer);


	lib->Add(ID_CAR_GUN_LEFT_WHITE, 83, 36, 83+7, 36+4, textPlayer);
	lib->Add(ID_CAR_GUN_RIGHT_WHITE, 84, 45, 84+7, 45+4, textPlayer);
	lib->Add(ID_CAR_GUN_UPLEFT_WHITE, 92, 34, 92+8, 34+8, textPlayer);
	lib->Add(ID_CAR_GUN_UPRIGHT_WHITE, 92, 43, 92+8, 43+8, textPlayer);
	lib->Add(ID_CAR_GUN_UP_WHITE, 103, 34, 103+4, 34+7, textPlayer);

	lib->Add(ID_CAR_HEAD_LEFT_WHITE, 74, 53, 74+16, 53+8, textPlayer);
	lib->Add(ID_CAR_HEAD_RIGHT_WHITE, 74, 62, 74+16, 62+8, textPlayer);
	lib->Add(ID_CAR_HEAD_UPLEFT_WHITE, 128, 54, 128+16, 54+15, textPlayer);
	lib->Add(ID_CAR_HEAD_UPRIGHT_WHITE, 110, 54, 110+16, 54+15, textPlayer);

	lib->Add(ID_CAR_BULLET_LEFT, 74, 3, 74 + 24, 3 + 6, textPlayer);
	lib->Add(ID_CAR_BULLET_RIGHT, 74, 12, 74 + 24, 12 + 6, textPlayer);
	lib->Add(ID_CAR_BULLET_UP, 100, 2, 100 + 6, 2 + 24, textPlayer);

	lib->Add(ID_TEXT_HOV, 0, 0, 11, 35, textPlayerHealth);
	lib->Add(ID_TEXT_POW, 0, 58, 11, 93, textPlayerHealth);
	lib->Add(ID_SOPHIA_HEALTH_BAR, 0, 43, 11, 48, textPlayerHealth);

	//lib->Add(ID_TEXT_HOV, 0, 0, 11 * 2, 35 * 2, textPlayerHealth);
	//lib->Add(ID_TEXT_POW, 0, 58 * 2, 11 * 2, 93 * 2, textPlayerHealth);
	//lib->Add(ID_SOPHIA_HEALTH_BAR, 0, 43 * 2, 11 * 2, 48 * 2, textPlayerHealth);

	// ENEMIES
	// WORM
	lib->Add(ID_WORM_MOVE_LEFT_1, 46, 412, 64, 422, textEnemies);
	lib->Add(ID_WORM_MOVE_LEFT_2, 64 , 412, 82, 422, textEnemies);
	lib->Add(ID_WORM_MOVE_RIGHT_1, 172, 412, 190, 422, textEnemies);
	lib->Add(ID_WORM_MOVE_RIGHT_2, 192, 412, 210, 422, textEnemies);

	// DOME
	lib->Add(ID_DOME_UP_MOVE_RIGHT_1, 67, 424, 85, 443, textEnemies);
	lib->Add(ID_DOME_UP_MOVE_RIGHT_2, 87, 424, 105, 443, textEnemies);
	lib->Add(ID_DOME_UP_MOVE_LEFT_1, 149, 424, 167, 443, textEnemies);
	lib->Add(ID_DOME_UP_MOVE_LEFT_2, 169, 424, 187, 443, textEnemies);

	lib->Add(ID_DOME_DOWN_MOVE_RIGHT_1, 67, 479, 85, 498, textEnemies);
	lib->Add(ID_DOME_DOWN_MOVE_RIGHT_2, 87, 479, 105, 498, textEnemies);
	lib->Add(ID_DOME_DOWN_MOVE_LEFT_1, 149, 479, 167, 498, textEnemies);
	lib->Add(ID_DOME_DOWN_MOVE_LEFT_2, 169, 479, 187, 498, textEnemies);

	lib->Add(ID_DOME_LEFT_MOVE_UP_1, 50, 461, 68, 479, textEnemies);
	lib->Add(ID_DOME_LEFT_MOVE_UP_2, 51, 441, 69, 459, textEnemies);
	lib->Add(ID_DOME_LEFT_MOVE_DOWN_1, 133, 441, 151, 459, textEnemies);
	lib->Add(ID_DOME_LEFT_MOVE_DOWN_2, 132, 461, 150, 479, textEnemies);

	lib->Add(ID_DOME_RIGHT_MOVE_UP_1, 187, 461, 205, 479, textEnemies);
	lib->Add(ID_DOME_RIGHT_MOVE_UP_2, 187, 441, 205, 459, textEnemies);
	lib->Add(ID_DOME_RIGHT_MOVE_DOWN_1, 105, 441, 123, 459, textEnemies);
	lib->Add(ID_DOME_RIGHT_MOVE_DOWN_2, 105, 461, 123, 479, textEnemies);


	//JUMPER
	lib->Add(ID_JUMPER_MOVE_LEFT_1, 67, 499, 84, 525, textEnemies);
	lib->Add(ID_JUMPER_MOVE_LEFT_2, 85, 499, 102, 525, textEnemies);
	lib->Add(ID_JUMPER_MOVE_LEFT_3, 105, 499, 122, 525, textEnemies);
	lib->Add(ID_JUMPER_MOVE_RIGHT_1, 132, 499, 149, 525, textEnemies);
	lib->Add(ID_JUMPER_MOVE_RIGHT_2, 152, 499, 169, 525, textEnemies);
	lib->Add(ID_JUMPER_MOVE_RIGHT_3, 170, 499, 187, 525, textEnemies);


	//ORB
	lib->Add(ID_ORB_1, 78, 387, 96, 405, textEnemies);
	lib->Add(ID_ORB_2, 98, 387, 116, 405, textEnemies);
	lib->Add(ID_ORB_3, 118, 387, 136, 405, textEnemies);
	lib->Add(ID_ORB_4, 138, 387, 156, 405, textEnemies);
	lib->Add(ID_ORB_5, 158, 387, 176, 405, textEnemies);


	//WALKER
	lib->Add(ID_WALKER_1, 84, 296, 102, 313, textEnemies);
	lib->Add(ID_WALKER_2, 104, 296, 122, 313, textEnemies);
	lib->Add(ID_WALKER_3, 132, 296, 150, 313, textEnemies);
	lib->Add(ID_WALKER_4, 152, 296, 170, 313, textEnemies);

	//84	296	18	17
	//	104	297	18	16

	//	132	297	18	16
	//	152	296	18	17
}

void CGame::LoadLevel()
{

	int tile_count, tile_width, tile_height, tile_count_width, tile_count_height;
	vector<int> solid_tiles;
	vector<int> anti_player_tiles;
	vector<vector<int>> matrix;
	string tileDir, fileDir;

	fileDir = "Resources/Textfile/TileMaTrix.txt";

	GetInfo(tile_count, tile_width, tile_height,
		tile_count_width, tile_count_height, 
		solid_tiles, anti_player_tiles,
		matrix, tileDir, fileDir);

	map<int, Box<int>> tileMap;
	GetMap(tile_width, tile_height, tile_count, tileMap);

	wstring stemp = std::wstring(tileDir.begin(), tileDir.end());
	LPTileSet tileSet = new CTileSet(
		CGraphic::Instance->LoadTexture(stemp.c_str()),
		tileMap, tile_width
	);

	CTileMap::GetInstance()->SetTileSet(tileSet);
	CTileMap::GetInstance()->SetMatrix(matrix);

	LoadWalls(matrix, solid_tiles, tile_width);
	LoadAntiPlayerZones(matrix, anti_player_tiles, tile_width);
}

inline void CGame::LoadWalls(
	vector<vector<int>> matrix, 
	vector<int> solid_tiles, 
	int tile_width)
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

	AddEntity(new CWall(0, 89 * 32, 32, 96 * 32), 0, 91 * 32);
}

void CGame::LoadAntiPlayerZones(
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

void CGame::LoadAreas()
{
	areas[1] = new CArea(0, 88, 31, 95);
	areas[2] = new CArea(32, 57, 47, 95);
	areas[3] = new CArea(48, 56, 63, 63);

	areas[4] = new CArea(64, 33, 79, 63);
	areas[5] = new CArea(48, 1, 63, 55);
	areas[6] = new CArea(64, 0, 79, 7);

	areas[7] = new CArea(80, 0, 95, 15);
	areas[8] = new CArea(64, 8, 79, 14);
	areas[9] = new CArea(40, 32, 47, 39);

	for (int i = 1; i <= 9; i++)
	{
		float l = areas[i]->left * 32;
		float t = areas[i]->top * 32;
		float r = areas[i]->right * 32 + 32;
		float b = areas[i]->bottom * 32 + 48;

		areas[i] = new CArea(l, t, r, b);
	}

	currArea = areas[1];
}

void CGame::LoadPortals()
{
	const int range = 16;
	int ls[range][5] = {
		{ 12, 30, 92, 31, 92 },
		{ 21, 33, 92, 33, 92 },
		{ 23, 46, 60, 46, 60 },
		{ 32, 49, 60, 49, 60 },
		{ 34, 62, 60, 62, 60 },
		{ 43, 65, 60, 65, 60 },

		{ 45, 65, 36, 65, 36},
		{ 54, 62, 36, 62, 36},
		{ 56, 62, 4, 62, 4},
		{ 65, 65, 4, 65, 4},
		{ 67, 78, 4, 78, 4},
		{ 76, 81, 4, 81, 4},

		{ 78, 81, 12, 81, 12},
		{ 87, 78, 12, 78, 12},
		{ 59, 49, 36, 49, 36},
		{ 95, 46, 36, 46, 36}
	};

	for (int i = 0; i < range; i++)
	{
		int id = ls[i][0];
		int areaId = id / 10;
		int reverseId = (id % 10) * 10 + (id / 10);

		int l = ls[i][1] * 32;
		int r = ls[i][3] * 32 + 32;

		int t = ls[i][2] * 32 ;
		int b = ls[i][4] * 32 + 32;

		portals[id] = new CPortal(l, t, r, b);
		portals[id]->SetTargetId(reverseId);
		portals[id]->SetAreaId(areaId);
	}
}

void CGame::LoadEnemies()
{
	AddEntity(new CWorm(), 160, 92 * 32);
	AddEntity(new COrb(), 1*32, 91 * 32);
	//AddEntity(new CWorm(), 180, 92 * 32);
	//AddEntity(new CWorm(), 200, 92 * 32);
	//AddEntity(new CWorm(), 220, 92 * 32);
	//AddEntity(new CWorm(), 240, 92 * 32);
	//AddEntity(new CWorm(), 260, 92 * 32);
	//AddEntity(new CWorm(), 280, 92 * 32);
	//AddEntity(new CWorm(), 300, 92 * 32);
}

void CGame::Run()
{
	//Load resource to the game
	LoadResources();

	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	try
	{
		while (!done)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) done = 1;

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			DWORD now = GetTickCount();

			// dt: the time between (beginning of last frame) and now
			// this frame: the frame we are about to render
			DWORD dt = now - frameStart;

			//Heart of the game
			if (dt >= tickPerFrame)
			{
				frameStart = now;

				Update(dt/10);
				Render();
			}
			//else
			//	Sleep(tickPerFrame - dt);
		}
	}
	catch (const std::exception& ex)
	{
		DebugOut(L"[ERROR] Exception in Run method in Game %s\n", ex.what());
		return;
	}

	//Clean the resources
	CleanResources();
}

void CGame::Update(DWORD dt)
{
	requestList.clear();

	/*
	struture of updating the game
	first we update game object collision box position base on game object position
	then we set game object state
	then with the state we set velocity, action
	then we calculate collision between game objects return remaining velocity
	then we update the game object position base on remaining velocity
	*/
	CInput::GetInstance()->Update();

	UpdateCollisionBoxes(dt);
	UpdateEnemies(dt);

	switch (mode)
	{
	case NORMAL_MODE:
		NormalMode(dt);
		break;

	case CHANGEAREA_MODE:
		TransitionMode(dt);
		break;

	default:
		break;
	}

	ExecuteRequests(requestList);
}

void CGame::UpdateCamera()
{
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

void CGame::UpdateCollisionBoxes(DWORD dt)
{
	float l, t, r, b;
	CCamera::GetInstance()->GetLTRB(l, t, r, b);
	int startX, startY, endX, endY;
	GetGridXandY(startX, startY, endX, endY, l, t, r, b,
		GRID_WIDTH, GRID_HEIGHT, grid_count_width, grid_count_height);

	CCollision::GetInstance()->ResetActiveCollisionBoxes();
	//since player is special not in the grid system,
	//ensure that player co box is always in active co box list
	//co box list contain all collision box
	//active co box list contain collision box that get checked collide
	CCollision::GetInstance()->AddActiveCollisionBoxes(
		CPlayer::GetCurrentPlayer()->GetCollisionBox()->GetId()
	);
	//base on grid, add collision box to the active list
	for (int i = startY; i <= endY; i++)
	{
		for (int j = startX; j <= endX; j++)
		{
			CCollision::GetInstance()
				->AddActiveCollisionBoxes(mapGrid[i][j].GetColBoxes());
		}
	}
}

void CGame::UpdateEnemies(DWORD dt)
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
			mapGrid[i][j].Update(dt, count);
		}
	}
}

void CGame::UpdatePlayer(DWORD dt)
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

void CGame::UpdatePortals(DWORD dt)
{
	for each (pair<int, CPortal*> por_pair in portals)
	{
		CPortal* portal = por_pair.second;
		int id = por_pair.first;
		int area1 = portal->GetAreaId();
		int area2 = portal->GetTargetId();

		portal->Update(dt);
		if (portal->IsCollideWithPlayer())
		{
			DebugOut(L"[DEBUG] Portal [%d] from area [%d] to area [%d]\n",
				id, area1, area2);
			SetAreaTransition(portal);
		}
	}
}

void CGame::SetAreaTransition(CPortal* p)
{
	//get cur area, dest area, dest position for player
	destPortal = portals[p->GetTargetId()];
	int destAreaId = destPortal->GetAreaId();
	destArea = areas[destAreaId];

	mode = CHANGEAREA_MODE;
}

void CGame::NormalMode(DWORD dt)
{
	CPlayer* player = CPlayer::GetCurrentPlayer();
	CCamera* cam = CCamera::GetInstance();

	UpdatePlayer(dt);
	UpdateCamera();
	UpdatePortals(dt);
}

void CGame::TransitionMode(DWORD dt)
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
		currArea = destArea;
		destPortal->SetIsCollideWithPlayer(true);
		player->Enable();
		mode = NORMAL_MODE;

		float portal_l, portal_t, portal_r, portal_b;
		destPortal->GetCollisionBox()->GetLTRB(
			portal_l, portal_t, portal_r, portal_b
		);
		
		float x, y;
		x = (portal_l + portal_r) / 2 -
			(player->GetCenter().x - player->GetPosition().x);
		y = (portal_b + portal_t) / 2 -
			(player->GetCenter().y - player->GetPosition().y);
		player->SetPosition(
			x, y
		);
	}
	else
	{
		cam->Move(min(6, dx) * sidex, min(6, dy) * sidey);
		player->Disable();
	}
}

void CGame::Render()
{
	LPDIRECT3DDEVICE9 d3ddev = CGraphic::Instance->GetDirect3DDevice();
	LPD3DXSPRITE spriteHandler = CGraphic::Instance->GetSpriteHandler();
	LPDIRECT3DSURFACE9 backBuffer = CGraphic::Instance->GetBackBuffer();

	if (d3ddev->BeginScene() == D3D_OK)
	{
		// Clear the whole window with a color
		d3ddev->ColorFill(backBuffer, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		//Render these
		//tiles -> enemies -> player -> portals
		RenderTiles();
		RenderEnemies();
		RenderPlayer();
		RenderPortals();

		spriteHandler->End();
		d3ddev->EndScene();
	}

	// Display back buffer content to the screen
	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void CGame::RenderTiles()
{
	CTileMap::GetInstance()->Render();
}

void CGame::RenderEnemies()
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
			mapGrid[i][j].Render();
		}
	}
}

void CGame::RenderPlayer()
{
	CPlayer::GetCurrentPlayer()->Render();
	CPlayerHealth::GetInstance()->Render();
}

void CGame::RenderPortals()
{
	for each (pair<int, CPortal*> por_pair in portals)
	{
		CPortal* portal = por_pair.second;

		portal->Render();
	}
}

void CGame::CleanResources()
{
	CGraphic::Instance->End();
}


CGame::~CGame()
{
}

void CGame::AddEntity(LPEntity entity, float x, float y)
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

void CGame::RemoveEntity(int id)
{
	LPEntity entity = mapEntities[id];

	int grid_x, grid_y;
	entity->GetGridPosition(grid_x, grid_y);

	mapGrid[grid_y][grid_x].RemoveEntity(id);

	mapEntities.erase(id);
	free(entity);
}

void CGame::SetEntity(LPEntity entity)
{
	if (entity == NULL) return;
	if (entity->GetId() < 0 || entity->GetId() > countId) return;

	int old_grid_x, old_grid_y;
	entity->GetGridPosition(old_grid_x, old_grid_y);
	if (!(old_grid_x < 0 || old_grid_y < 0 ||
		old_grid_x >= grid_count_width || old_grid_y >= grid_count_height))
	{
		mapGrid[old_grid_y][old_grid_x].RemoveEntity(entity->GetId());
	}

	int grid_x = entity->GetCenter().x / GRID_WIDTH;
	int grid_y = entity->GetCenter().y / GRID_HEIGHT;

	//assert code
	if (grid_x < 0 || grid_y < 0 ||
		grid_x >= grid_count_width || grid_y >= grid_count_height)
	{
		DebugOut(L"[ERROR] vector size violation at game ccp set entity\n");
		return;
	}

	mapGrid[grid_y][grid_x].AddEntity(entity->GetId());
	entity->SetGridPosition(grid_x, grid_y);

	//for debug
	ResetEntityCoCollisionBoxes(entity, grid_x, grid_y);
}

void CGame::ResetEntityCoCollisionBoxes(
	LPEntity entity, int grid_x, int grid_y)
{
	list<LPCollisionBox> newCoCollisionBoxes;
	list<CGrid*> selfAndSuroundGrids;
	selfAndSuroundGrids.push_back(&mapGrid[grid_y][grid_x]);
	if (grid_x > 0)
		selfAndSuroundGrids.push_back(&mapGrid[grid_y][grid_x - 1]);
	if (grid_x < grid_count_width - 1)
		selfAndSuroundGrids.push_back(&mapGrid[grid_y][grid_x + 1]);

	if (grid_y > 0)
		selfAndSuroundGrids.push_back(&mapGrid[grid_y - 1][grid_x]);
	if (grid_y < grid_count_height - 1)
		selfAndSuroundGrids.push_back(&mapGrid[grid_y + 1][grid_x]);

	if (grid_x > 0 && grid_y > 0)
		selfAndSuroundGrids.push_back(&mapGrid[grid_y - 1][grid_x - 1]);
	if (grid_x > 0 && grid_y < grid_count_height - 1)
		selfAndSuroundGrids.push_back(&mapGrid[grid_y + 1][grid_x - 1]);
	if (grid_x < grid_count_width - 1 && grid_y < grid_count_height - 1)
		selfAndSuroundGrids.push_back(&mapGrid[grid_y + 1][grid_x + 1]);
	if (grid_x < grid_count_width - 1 && grid_y > 0)
		selfAndSuroundGrids.push_back(&mapGrid[grid_y - 1][grid_x + 1]);

	for each (CGrid * grid in selfAndSuroundGrids)
	{
		for each (int id in grid->GetColBoxes())
			newCoCollisionBoxes.push_back(
				CCollision::GetInstance()->GetCollisionBox(id)
			);
	}

	entity->GetCollisionBox()->ResetCoCollisionBoxes(newCoCollisionBoxes);
}

LPEntity CGame::GetEntity(int id)
{
	return mapEntities[id];
}

void CGame::AddRequest(LPRequest re)
{
	requestList.push_back(re);
}

void CGame::ExecuteRequests(list<LPRequest> requests)
{
	while (!requests.empty())
	{
		LPRequest re = requests.front();

		ExecuteRequest(re);
		requests.pop_front();
	}
}

void CGame::ExecuteRequest(LPRequest request)
{
	switch (request->type)
	{
	case REQUEST_TYPES::CreateEntity:
		AddEntity(
			request->entity,
			request->x,
			request->y
		);
		break;
	case REQUEST_TYPES::DeleteEntity:
		RemoveEntity(request->id);
		break;
	case REQUEST_TYPES::SetEnetity:
		SetEntity(request->entity);
		break;
	default:
		break;
	}
}

void CGame::AddGameObject(LPGameObject gameObject)
{
	lGameObjects.push_back(gameObject);
}


HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	//Try this to see how the debug function prints out file and line 
	//wc.hInstance = (HINSTANCE)-100; 

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		DWORD ErrCode = GetLastError();
		MessageBox(hWnd, L"Error create window handle", L"Error", MB_OK);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}


LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		//if the player close the window
	case WM_DESTROY:
		//tell window to kill this program
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void GetGridXandY(
	int& startX, int& startY, int& endX, int& endY, 
	float left, float top, float right, float bottom, 
	float gridWidth, float gridHeight,
	int grid_count_width, 
	int grid_count_height)
{
	startX = max((left / gridWidth) - 1, 0);
	endX = min( right / gridWidth + 1, grid_count_width - 1);

	startY = max((top / gridHeight) - 1, 0);
	endY = min( bottom / gridHeight + 1, grid_count_height - 1);
}
