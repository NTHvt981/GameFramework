#include "Logic/Game.h"
#include "DirectWrapper/Graphic/Direct9GraphicAPI.h"
#include "DirectWrapper/Input/DirectInputAPI.h"
#include "DirectWrapper/Audio/DirectAudioAPI.h"
#include "Core/Macros/Macros.h"
#include "Core/GameSetting/GameSetting.h"
#include "Core/DataTypes/Duration.h"
#include <windows.h>
#include <tchar.h>
#include <cstdint>
#include <sysinfoapi.h>

HWND s_hwnd;
HWND CreateGameWindow(HINSTANCE hInstance, int64_t nCmdShow);
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void OnGameRequestShutdown();

std::unique_ptr<logic::Game> s_game = nullptr;
std::shared_ptr<core::GameSetting> s_gameSetting = nullptr;
bool s_isRunning = true;

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	s_gameSetting = std::make_unique<core::GameSetting>();
	s_gameSetting->SetFPS(60);
	s_gameSetting->SetWindowTitle("Blaster Master");
	s_gameSetting->SetWindowSize({ 256, 224 });

	s_hwnd = CreateGameWindow(hInstance, nCmdShow);

	MSG msg;
	bool done = 0;
	ULONGLONG currentFrameTime = GetTickCount64();
	ULONGLONG previousFrameTime = GetTickCount64();

	std::unique_ptr<graphics::INativeGraphicAPI> nativeRenderAPI = std::make_unique<graphics::Direct9GraphicAPI>(s_hwnd);
	std::unique_ptr<inputs::INativeInputAPI> nativeInputAPI = std::make_unique<inputs::DirectInputAPI>(s_hwnd, hInstance);
	std::unique_ptr<audios::INativeAudioAPI> nativeAudioAPI = std::make_unique<audios::DirectAudioAPI>(s_hwnd);
	
	s_game = std::make_unique<logic::Game>(
		std::move(nativeRenderAPI), 
		std::move(nativeInputAPI), 
		std::move(nativeAudioAPI),
		s_gameSetting
	);
	s_game->Initialize();

	RECT rect;
	bool result = GetClientRect(s_hwnd, &rect);
	DEBUG(assert(result));
	if (result)
	{
		uint64_t width = rect.right - rect.left;
		uint64_t height = rect.bottom - rect.top;
		s_game->OnResizeWindow(core::SizeUI64
			{
				width,
				height,
			}
		);
	}
	auto connection = s_game->sig_requestShutdown.Connect(std::function(OnGameRequestShutdown));
	
	RELEASE(
	try
	{
	)
		s_game->LoadResource();

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

			s_game->RunLoop(core::Duration::FromMilliseconds(currentFrameTime - previousFrameTime));

			previousFrameTime = currentFrameTime;
		}
	RELEASE(
	}
	catch (const std::exception& ex)
	{
		s_game->Shutdown();
		return -1;
	}
	)

	s_game->Shutdown();

	return 0;
}

HWND CreateGameWindow(HINSTANCE hInstance, int64_t nCmdShow)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	//Try this to see how the debug function prints out file and line 
	//wc.hInstance = (HINSTANCE)-100; 

	const std::wstring className = s_gameSetting->GetWindowTitle().ToStdWStr();

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = className.c_str();
	wc.hIconSm = NULL;

	ATOM result = RegisterClassEx(&wc);
	assert(result != NULL);

	DWORD windowStyle = WS_OVERLAPPEDWINDOW; // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
	core::SizeUI64 clientSize = s_gameSetting->GetWindowSize();
	RECT windowRect = RECT
	{
		100,
		100,
		100 + static_cast<int>(clientSize.width),
		100 + static_cast<int>(clientSize.height)
	};
	bool adjustResult = AdjustWindowRectEx(&windowRect, windowStyle, false, windowStyle);

	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		wc.lpszClassName,
		windowStyle,
		windowRect.left,
		windowRect.top,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
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
	// add special case check here
	if (message == WM_DESTROY) // when user click [x] button
	{
		PostQuitMessage(0);
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	if (s_game.get() == nullptr || (!s_game->IsInitialized()))
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	switch (message) {
	case WM_KILLFOCUS: // when user click outside window
	{
		s_game->Pause();
		break;
	}
	case WM_SETFOCUS: // when user click in window
	{
		s_game->Resume();
		break;
	}
	case WM_SIZE: // when user resize window
	{
		switch (wParam)
		{
		case SIZE_MAXHIDE: [[fallthrough]];
		case SIZE_MAXIMIZED: [[fallthrough]];
		case SIZE_MAXSHOW: [[fallthrough]];
		case SIZE_RESTORED: [[fallthrough]];
		{
			RECT rect;
			bool result = GetClientRect(s_hwnd, &rect);
			DEBUG(assert(result));
			if (result)
			{
				uint64_t width = rect.right - rect.left;
				uint64_t height = rect.bottom - rect.top;
				s_game->OnResizeWindow(core::SizeUI64
					{
						width,
						height,
					}
				);
			}
			break;
		}
		case SIZE_MINIMIZED: [[fallthrough]];
		default:
			break;
		}
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void OnGameRequestShutdown()
{
	s_isRunning = false;
}