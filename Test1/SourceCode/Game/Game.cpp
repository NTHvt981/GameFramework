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
	CInput::GetInstance()->Update();
}

void CGame::LoadResources()
{
	LoadTextures();
	LoadSprites();
	LoadAnimations();

	//AddEntity(new CHorizontalEntity(STEEL_ROBOT_TEXTURE_PATH), 300, 100);
	//AddEntity(new CVerticalEntity(STEEL_ROBOT_TEXTURE_PATH), 0, 100);
	AddEntity(new CPlayer(STEEL_ROBOT_TEXTURE_PATH), 100, 300);
	AddEntity(new CGround(0, 0, WINDOW_WIDTH/2, 50, true), 0, 0);
	AddEntity(new CGround(0, 100, WINDOW_WIDTH/2, 150, false), 0, 0);
}

void CGame::LoadTextures()
{
	//CTextureLibrary::GetInstance()->Add(CAR_TEXTURE, L"Resources/Texture/My car spritesheet.png");
	CTextureLibrary::GetInstance()->Add(CAR_TEXTURE, TEX_CAR_SPRIRESHEET_TRANSPARENT);
	CTextureLibrary::GetInstance()
		->Add(ID_TEX_BBOX, TEX_BBOX_PATH);
}

void CGame::LoadSprites()
{
	LPDIRECT3DTEXTURE9 textCar = CTextureLibrary::GetInstance()->Get(CAR_TEXTURE);
	CSpriteLibrary* lib = CSpriteLibrary::GetInstance();

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
	lib->Add(ID_CAR_WHEEL_8, 65	,2,	72,	9, textCar, 3, 4);
}

void CGame::LoadAnimations()
{
	LPAnimation ani = new CAnimation(1, 100);
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

	//for each (LPCollisionBox box in CCollision::GetInstance()->GetCollisionBoxes())
	//{
	//	box->Update();
	//}

	for each (LPGameObject obj in lGameObjects)
	{
		obj->Update(dt);
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

		CSpriteLibrary::GetInstance()->DrawTest();
		//CAnimationLibrary::GetInstance()->DrawTest();

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
	//lGameObjects.push_back(entity);
	AddGameObject(entity);
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