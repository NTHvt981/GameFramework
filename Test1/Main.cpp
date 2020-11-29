/* =============================================================
INTRODUCTION TO GAME PROGRAMMING SE102

SAMPLE 00 - INTRODUCTORY CODE

This sample illustrates how to:

1/ Create a window
2/ Initiate DirectX 9, Direct3D, DirectX Sprite
3/ Draw a static brick sprite to the screen
4/ Create frame rate independent movements

5/ Some good C programming practices
- Use constants whenever possible
- 0 Warnings

6/ Debug using __FILE__ __LINE__

WARNING: This one file example has a hell LOT of *sinful* programming practices
================================================================ */

#include "SourceCode\Game\Game.h"
#include "SourceCode\Constraints.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CGame* lGame = CGame::GetInstance();
	lGame->Init(hInstance, nCmdShow, WINDOW_WIDTH, WINDOW_HEIGHT, FULLSCREEN);
	lGame->Run();

	return 0;
}