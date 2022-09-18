#include <Windows.h>
#include "Game.h"
#include "Constraints.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CGame* lGame = CGame::GetInstance();
	lGame->Init(hInstance, nCmdShow, CAMERA_WIDTH * CAMERA_SCALE, CAMERA_HEIGHT * CAMERA_SCALE, FULLSCREEN);
	lGame->Run();

	return 0;
}