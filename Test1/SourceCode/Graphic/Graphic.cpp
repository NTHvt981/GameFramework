#include "Graphic.h"
#include "../Debug/Debug.h"

//CGraphic* CGraphic::GetInstance()
//{
//	if (__instance == NULL) __instance = new CGraphic();
//	return __instance;
//}

int CGraphic::Init(HWND hwnd) {
	this->hWnd = hwnd;

	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL)
	{
		MessageBox(hwnd, L"Error initializing Direct3D", L"Error", MB_OK);
		return 0;
	}

	D3DPRESENT_PARAMETERS d3dpp;

	/*
	Set up parameter to create directx device
	*/
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(this->hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	if (d3ddev == NULL)
	{
		//OutputDebugString(L"[ERROR] CreateDevice failed\n");
		MessageBox(hwnd, L"Error CreateDevice failed", L"Error", MB_OK);
		return 0;
	}

	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddev, &spriteHandler);

	OutputDebugString(L"[INFO] InitGame done;\n");
	return 1;
}

LPDIRECT3DTEXTURE9 CGraphic::LoadTexture(LPCWSTR texturePath)
{
	texturePath = L"./Resources/Texture/brick.png";

	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 texture;

	HRESULT result = D3DXGetImageInfoFromFile(texturePath, &info);
	if (result != D3D_OK)
	{
		//DebugOut(L"[ERROR] get image info failed. Result: %s\n", result);
		MessageBox(hWnd, L"Error get image info failed", L"Error", MB_OK);
		return NULL;
	}

	result = D3DXCreateTextureFromFileEx(
		d3ddev,								// Pointer to Direct3D device object
		texturePath,						// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255),			// Transparent color
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		//DebugOut(L"[ERROR] CreateTextureFromFile failed. File: %s\n", texturePath);
		MessageBox(hWnd, L"Error CreateTextureFromFile failed", L"Error", MB_OK);
		return NULL;
	}

	//DebugOut(L"[INFO] Texture loaded Ok: %s \n", texturePath);
	OutputDebugString(L"[INFO] Texture loaded Ok;\n");
	return texture;
}

void CGraphic::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom)
{
	D3DXVECTOR3 p(x, y, 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
}

void CGraphic::Render(LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddev->BeginScene())
	{
		// Clear the whole window with a color
		d3ddev->ColorFill(backBuffer, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		D3DXVECTOR3 p(BRICK_START_X, BRICK_START_Y, 0);
		spriteHandler->Draw(texture, NULL, NULL, &p, D3DCOLOR_WHITE);

		spriteHandler->End();
		d3ddev->EndScene();
	}

	// Display back buffer content to the screen
	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void CGraphic::End()
{
	d3d->Release();
	spriteHandler->Release();
	backBuffer->Release();
	d3ddev->Release();
}

