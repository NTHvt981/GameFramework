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
	AddGameObject(new CHorizontalEntity(STEEL_ROBOT_TEXTURE_PATH), 300, 100);
	AddGameObject(new CVerticalEntity(STEEL_ROBOT_TEXTURE_PATH), 0, 100);
	AddGameObject(new CPlayer(STEEL_ROBOT_TEXTURE_PATH), 0, 0);
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

	for each (LPCollisionBox box in CCollision::GetInstance()->GetCollisionBoxes())
	{
		box->Update();
	}

	for each (LPGameObject obj in lGameObjects)
	{
		obj->Update(dt);
	}
    return;
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

void CGame::AddGameObject(LPGameObject gameObject, float x, float y)
{
	gameObject->SetPosition(x, y);
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