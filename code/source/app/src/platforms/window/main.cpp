#include "Logic/Game.h"
#include "RenderDebug/DebugRenderAPI.h"
#include "RenderDirectx9/Directx9RenderAPI.h"
#include <windows.h>
#include <tchar.h>
#include <cstdint>
#include <sysinfoapi.h>

HWND CreateTestWindow(HINSTANCE hInstance, int64_t nCmdShow, int64_t ScreenWidth, int64_t ScreenHeight);
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void OnGameRequestShutdown();

std::unique_ptr<logic::Game> s_game;
bool s_isRunning = true;

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	HWND hwnd = CreateTestWindow(hInstance, nCmdShow, 800, 600);

	MSG msg;
	bool done = 0;
	ULONGLONG currentFrameTime = GetTickCount64();
	ULONGLONG previousFrameTime = GetTickCount64();

	std::unique_ptr<graphics::INativeRenderAPI> nativeRenderAPI = std::make_unique<graphics::DebugRenderAPI>();
	s_game = std::make_unique<logic::Game>(std::move(nativeRenderAPI));
	s_game->Initialize();
	auto connection = s_game->sig_requestShutdown.Connect(std::function(OnGameRequestShutdown));

	try
	{
		while (s_isRunning)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					s_isRunning = false;
				}

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			currentFrameTime = GetTickCount64();

			s_game->RunLoop(currentFrameTime - previousFrameTime);

			previousFrameTime = currentFrameTime;
		}
	}
	catch (const std::exception& ex)
	{
		s_game->Shutdown();
		return -1;
	}

	s_game->Shutdown();

	return 0;
}

HWND CreateTestWindow(HINSTANCE hInstance, int64_t nCmdShow, int64_t ScreenWidth, int64_t ScreenHeight)
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
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"Test-Win";
	wc.hIconSm = NULL;

	ATOM result = RegisterClassEx(&wc);
	assert(result != NULL);

	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		wc.lpszClassName,
		WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		ScreenWidth,
		ScreenHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	assert(hwnd != NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	return hwnd;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_KILLFOCUS:
		break;
	case WM_SETFOCUS:
		break;
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

void OnGameRequestShutdown()
{
	s_isRunning = false;
}