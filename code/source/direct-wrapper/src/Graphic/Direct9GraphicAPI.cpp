#include "DirectWrapper/Graphic/Direct9GraphicAPI.h"
#include "Core/DataTypes/Flag.h"
#include "Core/DataTypes/Box.h"
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
	assert(SUCCEEDED(result));

	m_direct3DDevice9->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_backBuffer);

	// Initialize spriteRef helper from Direct3DX helper library
	result = D3DXCreateSprite(m_direct3DDevice9, &m_spriteHandler);
	assert(SUCCEEDED(result));
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

void Direct9GraphicAPI::Draw(const DrawParams& i_drawParams)
{
	const core::TextureId id = i_drawParams.textureId;
	assert(m_mapTextures.contains(id));
	const LPDIRECT3DTEXTURE9 texture = m_mapTextures[id];

	const core::Vector2F pos = i_drawParams.position;
	D3DXVECTOR3 position(pos.x, pos.y, 0);

	const core::BoxI64 box = i_drawParams.boundary;
	RECT destRect;
	destRect.left = box.left;
	destRect.top = box.top;
	destRect.right = box.right;
	destRect.bottom = box.bottom;

	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);

	int64_t opacity = i_drawParams.alpha * 255.0;

	m_spriteHandler->SetTransform(&matrix);
	m_spriteHandler->Draw(texture, &destRect, NULL, &position, D3DCOLOR_RGBA(255, 255, 255, opacity));
}

////////////////////////////////////////////////////////////////////////////////

LPDIRECT3DTEXTURE9 Direct9GraphicAPI::CreateTextureFromFile(const core::String& imagePath)
{
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 o_texture;

	const wchar_t* rawPath = imagePath.ToWStr();
	HRESULT result = D3DXGetImageInfoFromFile(rawPath, &info);
	assert(SUCCEEDED(result));

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
	assert(SUCCEEDED(result));

	return o_texture;
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