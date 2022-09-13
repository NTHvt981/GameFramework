#pragma once
#include "IGraphics.h"
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9core.h>
#include <memory>

namespace graphics
{

class D9Graphics final : public IGraphics
{
public:
	D9Graphics(const HWND i_hwnd);
	~D9Graphics();

private:
	const HWND m_hwnd;
	LPDIRECT3D9 m_direct3D9;
	LPDIRECT3DDEVICE9 m_direct3DDevice9;
	LPDIRECT3DSURFACE9 m_backBuffer;
	LPD3DXSPRITE m_spriteHandler;
};

} // namespace graphics