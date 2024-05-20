#include "DirectWrapper/Graphic/Direct9API.h"
#include "Core/DataTypes/SpriteState.h"
#include "Core/DataTypes/Texture.h"
#include "Core/DataTypes/Flag.h"
#include "Core/DataTypes/Box.h"
#include "Core/Macros/Macros.h"
#include <assert.h>

namespace graphics
{

core::Flag s_initFlag;
core::Flag s_shutdownFlag;

Direct9API::Direct9API(const HWND i_hwnd)
	: m_hwnd(i_hwnd)
{
}

////////////////////////////////////////////////////////////////////////////////

Direct9API::~Direct9API()
{
	Shutdown();
}

////////////////////////////////////////////////////////////////////////////////

void Direct9API::Initialize()
{
	if (s_initFlag.IsSet())
	{
		return;
	}
	s_initFlag.Set();

	m_direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	assert(m_direct3D9 != nullptr);

	//Set up parameter to create directx device
	ZeroMemory(&m_direct3DParams, sizeof(m_direct3DParams));

	m_direct3DParams.Windowed = TRUE;
	m_direct3DParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_direct3DParams.BackBufferFormat = D3DFMT_X8R8G8B8;
	m_direct3DParams.BackBufferCount = 2;

	RECT clientRect;
	GetClientRect(m_hwnd, &clientRect);
	m_direct3DParams.BackBufferWidth = m_backBufferSize.width;
	m_direct3DParams.BackBufferHeight = m_backBufferSize.height;

	HRESULT result = m_direct3D9->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&m_direct3DParams,
		&m_direct3DDevice9);
	assert(SUCCEEDED(result));
	
	result = m_direct3DDevice9->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_backBuffer);
	assert(SUCCEEDED(result));

	// Initialize spriteRef helper from Direct3DX helper library
	result = D3DXCreateSprite(m_direct3DDevice9.Get(), &m_spriteHandler);
	assert(SUCCEEDED(result));
}

////////////////////////////////////////////////////////////////////////////////

void Direct9API::LoadTexture(
	const core::TextureId i_textureId, 
	const core::String i_textureFilePath)
{
	assert(!m_mapTextures.contains(i_textureId));
	m_mapTextures[i_textureId] = CreateTextureFromFile(i_textureFilePath);
}

////////////////////////////////////////////////////////////////////////////////

void Direct9API::SetViewportSize(const core::SizeF& i_viewportSize)
{
	m_viewportSize = i_viewportSize;
	ResetDrawMatrix();
}

////////////////////////////////////////////////////////////////////////////////

void Direct9API::SetViewportPosition(const core::Vector2F& i_viewportPosition)
{
	m_viewportPosition = i_viewportPosition;
	ResetDrawMatrix();
}

////////////////////////////////////////////////////////////////////////////////

void Direct9API::Draw(const DrawParams& i_drawParams)
{
	const core::TextureId id = i_drawParams.textureId;
	assert(m_mapTextures.contains(id));
	ComPtr<IDirect3DTexture9> texture = m_mapTextures[id];

	const core::Vector2F pos = i_drawParams.position;
	D3DXVECTOR3 position(pos.x, pos.y, 0);

	const core::Vector2F origin = i_drawParams.origin;
	D3DXVECTOR3 center(origin.x, origin.y, 0);

	const core::BoxI64 box = i_drawParams.textureBoundary;
	RECT srcRect;
	srcRect.left = (long) box.left;
	srcRect.top = (long) box.top;
	srcRect.right = (long) box.right;
	srcRect.bottom = (long) box.bottom;

	int64_t opacity = i_drawParams.alpha * 255.0;

	m_spriteHandler->Draw(
		texture.Get(), 
		&srcRect, 
		&center, 
		&position, 
		D3DCOLOR_RGBA(255, 255, 255, opacity)
	);
}

////////////////////////////////////////////////////////////////////////////////

void Direct9API::StartDraw()
{
	HRESULT result = m_direct3DDevice9->BeginScene();
	DEBUG(assert(SUCCEEDED(result)));

	result = m_direct3DDevice9->ColorFill(m_backBuffer.Get(), NULL, D3DCOLOR_XRGB(0, 0, 0));
	DEBUG(assert(SUCCEEDED(result)));

	result = m_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	DEBUG(assert(SUCCEEDED(result)));
}

////////////////////////////////////////////////////////////////////////////////

void Direct9API::EndDraw()
{
	HRESULT result = m_spriteHandler->End();
	DEBUG(assert(SUCCEEDED(result)));

	result = m_direct3DDevice9->EndScene();
	DEBUG(assert(SUCCEEDED(result)));

	result = m_direct3DDevice9->Present(NULL, NULL, NULL, NULL);
	DEBUG(assert(SUCCEEDED(result)));
}

////////////////////////////////////////////////////////////////////////////////

Microsoft::WRL::ComPtr<IDirect3DTexture9> Direct9API::CreateTextureFromFile(const core::String& imagePath)
{
	D3DXIMAGE_INFO info;
	ComPtr<IDirect3DTexture9> o_texture = nullptr;

	const wchar_t* rawPath = imagePath.ToWStr();
	HRESULT result = D3DXGetImageInfoFromFile(rawPath, &info);
	assert(SUCCEEDED(result));

	result = D3DXCreateTextureFromFileEx(
		m_direct3DDevice9.Get(),
		rawPath,
		info.Width,	
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		info.Format,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(251, 255, 0),	
		&info,
		NULL,
		&o_texture);

	assert(SUCCEEDED(result));

	return o_texture;
}

////////////////////////////////////////////////////////////////////////////////

void Direct9API::ResetDrawMatrix()
{
	float scaleWidth = (m_backBufferSize.width / m_viewportSize.width);
	float scaleHeight = (m_backBufferSize.height / m_viewportSize.height);
	float scale = scaleWidth < scaleHeight ? scaleWidth : scaleHeight;

	const D3DXVECTOR2 scaleVector = D3DXVECTOR2(
		scale,
		scale
	);

	const D3DXVECTOR2 translate = D3DXVECTOR2(
		m_viewportPosition.x, 
		m_viewportPosition.y
	);

	const D3DXVECTOR2 scaleOrigin = D3DXVECTOR2(0, 0);
	D3DXMATRIX drawMatrix;
	D3DXMatrixIdentity(&drawMatrix);
	D3DXMatrixTransformation2D(
		&drawMatrix,
		&scaleOrigin,
		NULL,
		&scaleVector,
		NULL,
		0,
		&translate
	);

	HRESULT result = m_spriteHandler->SetTransform(&drawMatrix);
	assert(SUCCEEDED(result));

	result = m_direct3DDevice9->TestCooperativeLevel();
	assert(SUCCEEDED(result));
}

////////////////////////////////////////////////////////////////////////////////

void Direct9API::Shutdown()
{
	if (s_shutdownFlag.IsSet())
	{
		return;
	}
	s_shutdownFlag.Set();

	for (auto& [id, texture] : m_mapTextures)
	{
		texture->Release();
	}

	m_spriteHandler->Release();
	m_backBuffer->Release();
	m_direct3DDevice9->Release();
	m_direct3D9->Release();
}

////////////////////////////////////////////////////////////////////////////////

void Direct9API::DrawAbsolute()
{
}

////////////////////////////////////////////////////////////////////////////////

void Direct9API::DrawRelative()
{
}

////////////////////////////////////////////////////////////////////////////////

core::APIMode Direct9API::GetAPIMode() const
{
	return core::APIMode::D3D9;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace graphics