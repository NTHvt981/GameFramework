#include "D9Graphics.h"
#include "Core/DataTypes/Flag.h"

#include <assert.h>

namespace graphics
{

data_types::Flag s_initFlag;

D9Graphics::D9Graphics(const HWND i_hwnd)
	: m_hwnd(i_hwnd)
{
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

	// Initialize sprite helper from Direct3DX helper library
	result = D3DXCreateSprite(m_direct3DDevice9, &m_spriteHandler);
	assert(SUCCEEDED(result));
}

D9Graphics::~D9Graphics()
{
	m_spriteHandler->Release();
	m_backBuffer->Release();
	m_direct3DDevice9->Release();
	m_direct3D9->Release();
}

} // namespace graphics