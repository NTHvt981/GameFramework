#pragma once

#include "..\Constraints.h"
#include <comdef.h>

class CGraphic
{
private:
	HWND hWnd;									// Window handle
	//static CGraphic* __instance;

	LPDIRECT3D9 d3d = NULL;		// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddev = NULL;	// Direct3D device object
	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

public:
	static CGraphic* Instance;
public:

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddev; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	int Init(HWND hwnd);
	LPDIRECT3DTEXTURE9 LoadTexture(LPCWSTR texturePath);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture);
	void Render(LPDIRECT3DTEXTURE9 texture);

	void End();
};

