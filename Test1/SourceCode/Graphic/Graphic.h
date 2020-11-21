#pragma once

#include "..\Constraints.h"
#include "..\Debug\Debug.h"
#include "../Camera/Camera.h"
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
	void Draw(
		LPDIRECT3DTEXTURE9 texture, float x, float y,
		int left, int top, int right, int bottom, 
		float origin_x=0, float origin_y=0, float alpha=1);
	void Draw(LPDIRECT3DTEXTURE9 texture, float x, float y, 
		float origin_x = 0, float origin_y = 0, float alpha = 1);
	void Draw(LPDIRECT3DTEXTURE9 texture, Vector position,
		Vector origin = Vector(0, 0), float alpha = 1);


	void DrawWithFixedPosition(
		LPDIRECT3DTEXTURE9 texture, float x, float y,
		int left, int top, int right, int bottom, float alpha = 1
	);
	void DrawWithTransformation(
		LPDIRECT3DTEXTURE9 texture, float x, float y,
		int left, int top, int right, int bottom, float alpha = 1
	);
	void SetRenderData(
		D3DXVECTOR2& center, D3DXVECTOR2& translate, D3DXVECTOR2& scaling);

	void Render(LPDIRECT3DTEXTURE9 texture);

	void End();
};

