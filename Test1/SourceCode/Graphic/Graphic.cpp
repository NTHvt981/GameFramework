#include "Graphic.h"

CGraphic* CGraphic::Instance = new CGraphic();

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
	HRESULT result = D3DXCreateSprite(d3ddev, &spriteHandler);
	//if (!SUCCEEDED(result))


	OutputDebugString(L"[INFO] Init graphic done;\n");
	return 1;
}

LPDIRECT3DTEXTURE9 CGraphic::LoadTexture(LPCWSTR texturePath)
{
	if (texturePath == NULL)
	{
		return NULL;
	}
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

	if (!SUCCEEDED(result))
	{
		_com_error err(result);
		LPCTSTR errMsg = err.ErrorMessage();
		DebugOut(L"[ERROR] CreateTextureFromFile failed. File: %s; Error Code: %s\n", texturePath, errMsg);
		return NULL;
	}

	DebugOut(L"[INFO] Texture loaded Ok: %s \n", texturePath);
	return texture;
}

void CGraphic::Draw(LPDIRECT3DTEXTURE9 texture, float x, float y,
	int left, int top, int right, int bottom,
	float origin_x, float origin_y, float alpha)
{
	int opacity = alpha * 255;
	D3DXVECTOR3 origin(origin_x, origin_y, 0);
	D3DXVECTOR3 position(x, y, 0);
	if (CCamera::GetInstance() != NULL)
	{
		CCamera::GetInstance()->SetMatrix();
		CCamera::GetInstance()->Transform(x, y, position);
	}
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	spriteHandler->Draw(texture, &r, &origin, &position, D3DCOLOR_RGBA(255, 255, 255, opacity));
	
}

void CGraphic::Draw(LPDIRECT3DTEXTURE9 texture, float x, float y,
	float origin_x, float origin_y, float alpha)
{
	int opacity = alpha * 255;
	D3DXVECTOR3 position(x, y, 0);
	if (CCamera::GetInstance() != NULL)
	{
		CCamera::GetInstance()->SetMatrix();
		CCamera::GetInstance()->Transform(x, y, position);
	}
	D3DXVECTOR3 origin(origin_x, origin_y, 0);
	spriteHandler->Draw(texture, NULL, &origin, &position, D3DCOLOR_RGBA(255, 255, 255, opacity));
}

void CGraphic::Draw(LPDIRECT3DTEXTURE9 texture, Vector position, Vector origin, float alpha)
{
	Draw(texture, position.x, position.y, origin.x, origin.y, alpha);
}

void CGraphic::Render(LPDIRECT3DTEXTURE9 texture)
{
}

void CGraphic::End()
{
	d3d->Release();
	spriteHandler->Release();
	backBuffer->Release();
	d3ddev->Release();
}

