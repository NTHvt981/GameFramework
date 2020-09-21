#include <d3d9.h>
#include <d3dx9.h>

#pragma once
class CGame
{
private:
	HWND hWnd;									// Window handle
	static CGame* _instance;

public:
	static CGame* GetInstance() { return _instance; }

	void Init(HWND hWnd);
	int Update(DWORD dt);
	int Render();

	~CGame();
};

