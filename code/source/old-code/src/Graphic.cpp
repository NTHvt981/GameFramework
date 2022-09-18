#include "GraphicSystem/Graphic.h"
#include <iosfwd>
#include <sys/stat.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <assert.h>

CGraphic* CGraphic::Instance = new CGraphic();

static const LPCWSTR sk_prefix = L"\\..\\data\\";

int64_t CGraphic::Init(HWND hwnd) {
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

	HRESULT result = d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	if (d3ddev == NULL)
	{
		throw("CreateDevice fail, error code: %d", result);
	}

	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	HRESULT result = D3DXCreateSprite(d3ddev, &spriteHandler);
	if (!SUCCEEDED(result))
	{
		throw("D3DXCreateSprite fail, error code: %d", result);
	}

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

	std::wstring totalPath = sk_prefix + std::wstring(texturePath);

	const auto currentPath = GetCurrentPath();
	const bool fileExist = IsFileExist(currentPath + totalPath);

	HRESULT result = D3DXGetImageInfoFromFile((currentPath + totalPath).c_str(), &info);
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
		D3DCOLOR_XRGB(251, 255, 0),			// Transparent color
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

void CGraphic::Draw(
	LPDIRECT3DTEXTURE9 texture, float x, float y,
	int64_t left, int64_t top, int64_t right, int64_t bottom,
	float origin_x, float origin_y, float alpha)
{
	if (CCamera::GetInstance() != NULL)
	{
		DrawWithTransformation(texture, x, y, left, top, right, bottom, alpha);
		return;
	}

	D3DXMATRIX matrix;

	int64_t opacity = alpha * 255;
	D3DXVECTOR3 origin(origin_x, origin_y, 0);
	D3DXVECTOR3 position(x, y, 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;

	spriteHandler->Draw(texture, &r, &origin, &position, D3DCOLOR_RGBA(255, 255, 255, opacity));
}

void CGraphic::Draw(LPDIRECT3DTEXTURE9 texture, 
	float x, float y,
	float origin_x, float origin_y, float alpha)
{
	int64_t opacity = alpha * 255;
	D3DXVECTOR3 position(x, y, 0);
	D3DXVECTOR3 origin(origin_x, origin_y, 0);
	spriteHandler->Draw(texture, NULL, &origin, &position, 
		D3DCOLOR_RGBA(255, 255, 255, opacity));
}

void CGraphic::DrawWithFixedPosition(
	LPDIRECT3DTEXTURE9 texture, float x, float y, 
	int64_t left, int64_t top, int64_t right, int64_t bottom, float alpha)
{
	int64_t opacity = alpha * 255;
	D3DXVECTOR3 position(x, y, 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;

	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	
	spriteHandler->SetTransform(&matrix);

	spriteHandler->Draw(texture, &r, NULL, &position, 
		D3DCOLOR_RGBA(255, 255, 255, opacity));
}

void CGraphic::DrawWithTransformation(
	LPDIRECT3DTEXTURE9 texture, float x, float y, 
	int64_t left, int64_t top, int64_t right, int64_t bottom, float alpha)
{
	int64_t opacity = alpha * 255;
	int64_t scale = CCamera::GetInstance()->GetScale();

	float width = right - left;
	float height = bottom - top;
	D3DXVECTOR2 center = D3DXVECTOR2((width / 2) * scale, (height / 2) * scale);
	D3DXVECTOR2 translate = D3DXVECTOR2(x, y);
	D3DXVECTOR2 scaling = D3DXVECTOR2(scale, scale);
	float angle = 0;
	SetRenderData(center, translate, scaling);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	D3DXMATRIX matrix;
	const D3DXVECTOR2 scaleCenter{0, 0};
	D3DXMatrixTransformation2D(
		&matrix,
		&scaleCenter,
		NULL,
		&scaling,
		NULL,
		angle,
		&translate
	);

	spriteHandler->SetTransform(&matrix);
	D3DXVECTOR3 Pos(0, 0, 0);
	spriteHandler->Draw(texture, &r, NULL, &Pos,
		D3DCOLOR_RGBA(255, 255, 255, opacity));
}

void CGraphic::SetRenderData(D3DXVECTOR2& center, D3DXVECTOR2& translate, D3DXVECTOR2& scaling)
{
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);

	Vector position = CCamera::GetInstance()->GetPosition();
	int64_t scale = CCamera::GetInstance()->GetScale();

	mt._11 = scale;
	mt._22 = scale;
	mt._33 = scale;
	mt._44 = scale;

	mt._41 = -position.x * scale;
	mt._42 = -position.y * scale;
	D3DXVECTOR4 curTranslate;
	D3DXVECTOR4 curCenter;

	const D3DXVECTOR2 scaleCenter{ center.x, center.y };
	D3DXVec2Transform(&curCenter, &scaleCenter, &mt);

	const D3DXVECTOR2 scaleCenter2{ translate.x, translate.y };
	D3DXVec2Transform(&curTranslate, &scaleCenter2, &mt);

	center.x = curCenter.x;
	center.y = curCenter.y;
	translate.x = curTranslate.x;
	translate.y = curTranslate.y;
}

void CGraphic::Draw(LPDIRECT3DTEXTURE9 texture, Vector position, Vector origin, float alpha)
{
	Draw(texture, position.x, position.y, origin.x, origin.y, alpha);
}

void CGraphic::End()
{
	d3d->Release();
	spriteHandler->Release();
	backBuffer->Release();
	d3ddev->Release();
}

