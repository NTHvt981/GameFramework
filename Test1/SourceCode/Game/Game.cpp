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
}

void CGame::LoadResources()
{
	LoadTextures();
	LoadSprites();
	LoadAnimations();
	LoadLevel();

	CPlayer* player = new CPlayer();
	player->SetPosition(100, 800);
	AddGameObject(player);
	CPlayer::SetCurrentPlayer(player);

	AddEntity(new CWorm(), 50, 100);
	AddEntity(new CWalker(), 50, 50);
	AddEntity(new CDome(), 50, 50);
	AddEntity(new CJumper(), 50, 150);
	AddEntity(new COrb(), 50, 50);

	AddEntity(new CGround(0, 0, 100, 32), 0, 0);
	AddEntity(new CGround(100, 64, 300, 96), 100, 64);
	AddEntity(new CGround(300, 128, 400, 160), 300, 128);
	AddEntity(new CGround(200, 192, 300, 224), 200, 192);
}

void CGame::LoadTextures()
{
	//CTextureLibrary::GetInstance()->Add(CAR_TEXTURE, L"Resources/Texture/My car spritesheet.png");
	CTextureLibrary::GetInstance()->Add(CAR_TEXTURE, TEX_CAR_SPRIRESHEET_TRANSPARENT);
	CTextureLibrary::GetInstance()->Add(ENEMIES_TEXTURE, ENEMIES_TEXTURE_PATH);
	CTextureLibrary::GetInstance()
		->Add(ID_TEX_BBOX, TEX_BBOX_PATH);
}

void CGame::LoadSprites()
{
	LPDIRECT3DTEXTURE9 textCar = CTextureLibrary::GetInstance()->Get(CAR_TEXTURE);
	LPDIRECT3DTEXTURE9 textEnemies = CTextureLibrary::GetInstance()->Get(ENEMIES_TEXTURE);
	CSpriteLibrary* lib = CSpriteLibrary::GetInstance();

	// CAR
	lib->Add(ID_CAR_GUN_LEFT, 11, 2, 18, 9, textCar, 12, 4);
	lib->Add(ID_CAR_GUN_RIGHT, 11, 11, 18, 18, textCar, -4, 4);
	lib->Add(ID_CAR_GUN_UPLEFT, 20, 2, 27, 9, textCar, 13, 13);
	lib->Add(ID_CAR_GUN_UPRIGHT, 20, 11, 27, 18, textCar, -5, 12);
	lib->Add(ID_CAR_GUN_UP, 29, 2, 36, 9, textCar, 4, 13);

	lib->Add(ID_CAR_HEAD_LEFT, 2,	20,	17,	27, textCar, 5, 8);
	lib->Add(ID_CAR_HEAD_RIGHT, 2,	29,	17,	36, textCar, 11, 8);
	lib->Add(ID_CAR_HEAD_UPLEFT, 56,	20,	71,	36, textCar, 3, 12);
	lib->Add(ID_CAR_HEAD_UPRIGHT, 38,	20,	53,	35, textCar, 12, 12);
	lib->Add(ID_CAR_BODY, 108,	2,	115,	9, textCar, 4, 6);

	lib->Add(ID_CAR_WHEEL_1, 38, 11, 45, 18, textCar, 4, 4);
	lib->Add(ID_CAR_WHEEL_2, 47, 11, 54, 18, textCar, 4, 4);
	lib->Add(ID_CAR_WHEEL_3, 56, 11, 63, 18, textCar, 4, 4);
	lib->Add(ID_CAR_WHEEL_4, 65, 11, 72, 18, textCar, 4, 4);
	lib->Add(ID_CAR_WHEEL_5, 38, 2, 45, 9, textCar, 3, 4);
	lib->Add(ID_CAR_WHEEL_6, 47, 2, 54, 9, textCar, 3, 4);
	lib->Add(ID_CAR_WHEEL_7, 56, 2, 63, 9, textCar, 3, 4);
	lib->Add(ID_CAR_WHEEL_8, 65, 2, 72, 9, textCar, 3, 4);

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

void CGame::LoadAnimations()
{
	LPAnimation ani = new CAnimation(1, 100);
}

void CGame::LoadLevel()
{
	int tile_size_x, tile_size_y, tileset_size_x, tileset_size_y;
	int padding, margin;
	vector<vector<int>> matrix;
	string tileDir, fileDir;

	fileDir = "Resources/Textfile/temp_tilemap_info.txt";

	GetInfo(
		tile_size_x, tile_size_y,
		tileset_size_x, tileset_size_y,
		padding, margin, matrix,
		tileDir, fileDir);

	map<int, Box<int>> tileMap;
	GetMap(tile_size_x, tile_size_x,
		tileset_size_x, tileset_size_y,
		padding, margin,
		tileMap);

	wstring stemp = std::wstring(tileDir.begin(), tileDir.end());
	LPTileSet tileSet = new CTileSet(
		CGraphic::Instance->LoadTexture(stemp.c_str()),
		tileMap, tile_size_x
	);

	CTileMap::GetInstance()->SetTileSet(tileSet);
	CTileMap::GetInstance()->SetMatrix(matrix);

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
			else
				Sleep(tickPerFrame - dt);
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
	/*
	struture of updating the game
	first we update game object collision box position base on game object position
	then we set game object state
	then with the state we set velocity, action
	then we calculate collision between game objects return remaining velocity
	then we update the game object position base on remaining velocity
	*/
	CInput::GetInstance()->Update();

	float l, t, r, b;
	CCamera::GetInstance()->GetLTRB(l, t, r, b);
	int startX, startY, endX, endY;
	GetGridXandY(startX, startY, endX, endY, l, t, r, b, GRID_WIDTH, GRID_HEIGHT);

	int count = 0;

	CCollision::GetInstance()->ResetActiveCollisionBoxes();
	CCollision::GetInstance()->AddActiveCollisionBoxes(
		CPlayer::GetCurrentPlayer()->GetCollisionBox()->GetId()
	);
	for (int i = startY; i <= endY; i++)
	{
		for (int j = startX; j <= endX; j++)
		{
			CCollision::GetInstance()
				->AddActiveCollisionBoxes(mapGrid[i][j].GetColBoxes());
		}
	}

	for (int i = startY; i <= endY; i++)
	{
		for (int j = startX; j <= endX; j++)
		{
			mapGrid[i][j].Update(dt, count);
		}
	}

	//update game object list (including player)
	for each (LPGameObject obj in lGameObjects)
	{
		obj->Update(dt);
	}

	//DebugOut(L"[INFO] Number of entities: %d\n", mapEntities.size());
	//DebugOut(L"[INFO] Number of entities update: %d\n", count);
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

		//CSpriteLibrary::GetInstance()->DrawTest();
		//CAnimationLibrary::GetInstance()->DrawTest();
		CTileMap::GetInstance()->Render();

		float l, t, r, b;
		CCamera::GetInstance()->GetLTRB(l, t, r, b);
		int startX, startY, endX, endY;
		GetGridXandY(startX, startY, endX, endY, l, t, r, b, GRID_WIDTH, GRID_HEIGHT);

		int count = 0;

		for (int i = startY; i <= endY; i++)
		{
			for (int j = startX; j <= endX; j++)
			{
				mapGrid[i][j].Render();
			}
		}

		//render game object list (including player)
		for each (LPGameObject obj in lGameObjects)
		{
			obj->Render();
		}

		spriteHandler->End();
		d3ddev->EndScene();
	}

	// Display back buffer content to the screen
	d3ddev->Present(NULL, NULL, NULL, NULL);
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

	SetEntity(entity);
}

void CGame::SetEntity(LPEntity entity)
{
	int grid_x = entity->GetPosition().x / GRID_WIDTH;
	int grid_y = entity->GetPosition().y / GRID_HEIGHT;

	mapGrid[grid_y][grid_x].AddEntity(entity->GetId());
}

LPEntity CGame::GetEntity(int id)
{
	return mapEntities[id];
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

void GetGridXandY(int& startX, int& startY, int& endX, int& endY, 
	float left, float top, float right, float bottom, 
	float gridWidth, float gridHeight)
{
	startX = max( (left / GRID_WIDTH) - 1, 0);
	endX = ceil(right / GRID_WIDTH);

	startY = max((top / GRID_HEIGHT) - 1, 0);
	endY = ceil(bottom / GRID_HEIGHT);
}
