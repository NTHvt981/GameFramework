#include "FileSystem/FileSystem.h"
#include "GraphicSystem/GraphicSystem.h"
#include <windows.h>
#include <tchar.h>
#include <cstdint>

namespace test
{
HWND CreateTestWindow(HINSTANCE hInstance, int64_t nCmdShow, int64_t ScreenWidth, int64_t ScreenHeight);
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
} // namespace test

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	HWND hwnd = test::CreateTestWindow(hInstance, nCmdShow, 800, 600);

	std::shared_ptr<files::FileSystem> fileSystem = std::make_shared<files::FileSystem>();
	fileSystem->Initialize();

	std::shared_ptr<graphics::GraphicSystem> graphicSystem = std::make_shared<graphics::GraphicSystem>(fileSystem);
	graphics::GraphicSystem::InitParams initParam;
	initParam.apiMode = core::APIMode::D3D9;
	initParam.optHwnd = hwnd;
	graphicSystem->Initialize(initParam);

	graphicSystem.reset();
	fileSystem.reset();

	return 0;
}

namespace test
{


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

} // namespace test