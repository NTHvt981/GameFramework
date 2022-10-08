#include "DirectWrapper/Graphic/Direct9GraphicAPI.h"
#include "GraphicSystem/DataTypes/SpriteState.h"
#include "GraphicSystem/DataTypes/Texture.h"
#include "Core/DataTypes/Flag.h"
#include "Core/DataTypes/Box.h"
#include "Core/Macros/Macros.h"
#include <assert.h>

namespace graphics
{

core::Flag s_initFlag;
core::Flag s_shutdownFlag;

Direct9GraphicAPI::Direct9GraphicAPI(const HWND i_hwnd)
	: m_hwnd(i_hwnd)
{
}

////////////////////////////////////////////////////////////////////////////////

Direct9GraphicAPI::~Direct9GraphicAPI()
{
	Shutdown();
}

////////////////////////////////////////////////////////////////////////////////

void Direct9GraphicAPI::Initialize()
{
	if (s_initFlag.IsSet())
	{
		return;
	}
	s_initFlag.Set();

	m_direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	assert(m_direct3D9 != nullptr);

	D3DPRESENT_PARAMETERS d3dparams;

	//Set up parameter to create directx device
	ZeroMemory(&d3dparams, sizeof(d3dparams));

	d3dparams.Windowed = TRUE;
	d3dparams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dparams.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dparams.BackBufferCount = 1;

	RECT windowRect;
	GetClientRect(m_hwnd, &windowRect);

	d3dparams.BackBufferHeight = windowRect.bottom + 1;
	d3dparams.BackBufferWidth = windowRect.right + 1;

	HRESULT result = m_direct3D9->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dparams,
		&m_direct3DDevice9);
	DEBUG(assert(SUCCEEDED(result)));
	
	result = m_direct3DDevice9->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_backBuffer);
	DEBUG(assert(SUCCEEDED(result)));

	// Initialize spriteRef helper from Direct3DX helper library
	result = D3DXCreateSprite(m_direct3DDevice9, &m_spriteHandler);
	DEBUG(assert(SUCCEEDED(result)));
}

////////////////////////////////////////////////////////////////////////////////

void Direct9GraphicAPI::LoadTexture(
	const core::TextureId i_textureId, 
	const core::String i_textureFilePath)
{
	assert(!m_mapTextures.contains(i_textureId));
	m_mapTextures[i_textureId] = CreateTextureFromFile(i_textureFilePath);
}

////////////////////////////////////////////////////////////////////////////////

void Direct9GraphicAPI::SetWindowSize(const core::SizeF i_screenSize)
{
	m_windowSize = i_screenSize;
	ResetDrawMatrix();
}

////////////////////////////////////////////////////////////////////////////////

void Direct9GraphicAPI::SetViewportSize(const core::SizeF& i_viewportSize)
{
	m_viewportSize = i_viewportSize;
	ResetDrawMatrix();
}

////////////////////////////////////////////////////////////////////////////////

void Direct9GraphicAPI::SetViewportPosition(const core::Vector2F& i_viewportPosition)
{
	m_viewportPosition = i_viewportPosition;
	ResetDrawMatrix();
}

////////////////////////////////////////////////////////////////////////////////

void Direct9GraphicAPI::Draw(const DrawParams& i_drawParams)
{
	const core::TextureId id = i_drawParams.textureId;
	assert(m_mapTextures.contains(id));
	const LPDIRECT3DTEXTURE9 texture = m_mapTextures[id];

	const core::Vector2F pos = i_drawParams.position;
	D3DXVECTOR3 position(pos.x, pos.y, 0);

	const core::BoxI64 box = i_drawParams.textureBoundary;
	RECT destRect;
	destRect.left = (long) box.left;
	destRect.top = (long) box.top;
	destRect.right = (long) box.right;
	destRect.bottom = (long) box.bottom;

	int64_t opacity = i_drawParams.alpha * 255.0;

	m_spriteHandler->Draw(texture, &destRect, NULL, &position, D3DCOLOR_RGBA(255, 255, 255, opacity));
}

////////////////////////////////////////////////////////////////////////////////

void Direct9GraphicAPI::StartDraw()
{
	HRESULT result = m_direct3DDevice9->BeginScene();
	DEBUG(assert(SUCCEEDED(result)));

	result = m_direct3DDevice9->ColorFill(m_backBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
	DEBUG(assert(SUCCEEDED(result)));

	result = m_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	DEBUG(assert(SUCCEEDED(result)));
}

////////////////////////////////////////////////////////////////////////////////

void Direct9GraphicAPI::EndDraw()
{
	HRESULT result = m_spriteHandler->End();
	DEBUG(assert(SUCCEEDED(result)));

	result = m_direct3DDevice9->EndScene();
	DEBUG(assert(SUCCEEDED(result)));

	result = m_direct3DDevice9->Present(NULL, NULL, NULL, NULL);
	DEBUG(assert(SUCCEEDED(result)));
}

////////////////////////////////////////////////////////////////////////////////

LPDIRECT3DTEXTURE9 Direct9GraphicAPI::CreateTextureFromFile(const core::String& imagePath)
{
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 o_texture;

	const wchar_t* rawPath = imagePath.ToWStr();
	HRESULT result = D3DXGetImageInfoFromFile(rawPath, &info);
	DEBUG(assert(SUCCEEDED(result)));

	result = D3DXCreateTextureFromFileEx(
		m_direct3DDevice9,
		rawPath,
		info.Width,	
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(251, 255, 0),	
		&info,
		NULL,
		&o_texture);
	DEBUG(assert(SUCCEEDED(result)));

	return o_texture;
}

////////////////////////////////////////////////////////////////////////////////

void Direct9GraphicAPI::ResetDrawMatrix()
{
	float scaleWidth = m_windowSize.width / m_viewportSize.width;
	float scaleHeight = m_windowSize.height / m_viewportSize.height;
	float scale = scaleWidth < scaleHeight ? scaleWidth : scaleHeight;

	const D3DXVECTOR2 scaleVector = D3DXVECTOR2(
		scaleWidth,
		scaleHeight
	);

	const D3DXVECTOR2 translate = D3DXVECTOR2(
		m_viewportPosition.x, 
		m_viewportPosition.y
	);

	const D3DXVECTOR2 scaleOrigin = D3DXVECTOR2(0, 0);

	D3DXMatrixTransformation2D(
		&m_drawMatrix,
		&scaleOrigin,
		NULL,
		&scaleVector,
		NULL,
		0,
		&translate
	);

	HRESULT result = m_spriteHandler->SetTransform(&m_drawMatrix);
	DEBUG(assert(SUCCEEDED(result)));
}

////////////////////////////////////////////////////////////////////////////////

void Direct9GraphicAPI::Shutdown()
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

void Direct9GraphicAPI::DrawAbsolute()
{
}

////////////////////////////////////////////////////////////////////////////////

void Direct9GraphicAPI::DrawRelative()
{
}

////////////////////////////////////////////////////////////////////////////////

core::APIMode Direct9GraphicAPI::GetAPIMode() const
{
	return core::APIMode::D3D9;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace graphics