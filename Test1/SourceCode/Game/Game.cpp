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
}

void CGame::LoadResources()
{
	lGameObjects.push_back(new CHorizontalEntity(STEEL_ROBOT_TEXTURE_PATH));
	lGameObjects.push_back(new CVerticalEntity(STEEL_ROBOT_TEXTURE_PATH));
	lGameObjects.push_back(new CPlayer(STEEL_ROBOT_TEXTURE_PATH));
	for each (LPGameObject obj in lGameObjects)
	{
		obj->SetPosition(POSITION_START_X, POSITION_START_Y);
	}
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

				Update(dt);
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
	then we move the game object base on remaining velocity
	*/
	CInput::GetInstance()->Update();
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

void CGame::SweptAABB(
	float move_left, float move_top, float move_right, float move_bottom,
	float move_velocity_x, float move_velocity_y,
	float static_left, float static_top, float static_right, float static_bottom,
	float& collide_time,
	float& normal_x,
	float& normal_y)
{
	float entry_x, entry_y;
	float exit_x, exit_y;
	/*
	what is entry and exit, look at this
  move_l		 move_r	   static_l			static_r
	|	  move		|			|	 static		|
					<---entry--->
	<-------------------exit-------------------->
	this illustrate the horizontal axis
	the same can be said for the vertical axis
	*/

	if (move_velocity_x > 0.0f)
	{
		entry_x = static_left - move_right;
		exit_x = static_right - static_left;
	}
	else
	{
		entry_x = static_right - static_left;
		exit_x = static_left - move_right;
	}

	if (move_velocity_y > 0.0f)
	{
		entry_y = static_top - move_bottom;
		exit_y = static_bottom - move_top;
	}
	else
	{
		entry_y = static_bottom - move_top;
		exit_y = static_top - move_bottom;
	}

	// find time of collision and time of leaving for
	// each axis(if statement is to prevent divide by zero)
	float entry_time_x, entry_time_y;
	float exit_time_x, exit_time_y;

	//we will devide entry position to velocity to get the entry time
	//for x entry_x / velocity_x
	//what if velocity == 0 ? asign entry time to infinity
	//the same goes for exit time, exit position
	if (move_velocity_x == 0.0f)
	{
		entry_time_x = -std::numeric_limits<float>::infinity();
		exit_time_x = std::numeric_limits<float>::infinity();
	}
	else
	{
		entry_time_x = entry_x / move_velocity_x;
		exit_time_x = exit_x / move_velocity_x;
	}

	if (move_velocity_y == 0.0f)
	{
		entry_time_y = -std::numeric_limits<float>::infinity();
		exit_time_y = std::numeric_limits<float>::infinity();
	}
	else
	{
		entry_time_y = entry_y / move_velocity_y;
		exit_time_y = exit_y / move_velocity_y;
	}

	float entry_time = max(entry_time_x, entry_time_y);
	float exit_time = min(exit_time_x, exit_time_y);

	// if there was no collision
	if (entry_time > exit_time ||
		entry_x < 0.0f && entry_y < 0.0f || 
		entry_x > 1.0f || entry_y > 1.0f)
	//collide time return 0 -> no collision
	{
		normal_x = 0.0f;
		normal_y = 0.0f;
		collide_time = 1.0f;
	}
	else //I dont understand these line
	{
		if (entry_time_x > entry_time_y)
		{
			if (entry_x < 0.0f)
			{
				normal_x = 1.0f;
				normal_y = 0.0f;
			}
			else
			{
				normal_x = -1.0f;
				normal_y = 0.0f;
			}
		}
		else
		{
			if (entry_y < 0.0f)
			{
				normal_x = 0.0f;
				normal_y = 1.0f;
			}
			else
			{
				normal_x = 0.0f;
				normal_y = -1.0f;
			}
		}
	}
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