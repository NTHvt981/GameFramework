#pragma once
#include "GraphicSystem/Graphics/IGraphics.h"
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9core.h>
#include <memory>
#include <unordered_map>

namespace graphics
{

class D9Graphics final : public IGraphics
{
public:
	D9Graphics(const HWND i_hwnd);
	~D9Graphics();

	// Inherited via IGraphics
	virtual void LoadTexture(
		const ids::TextureId i_textureId, 
		const data_types::String i_textureFilePath
	) override;
	virtual void Draw(const DrawParams& i_drawParams) override;

private:
	const HWND m_hwnd;
	LPDIRECT3D9 m_direct3D9;
	LPDIRECT3DDEVICE9 m_direct3DDevice9;
	LPDIRECT3DSURFACE9 m_backBuffer;
	LPD3DXSPRITE m_spriteHandler;

	std::unordered_map<ids::TextureId, LPDIRECT3DTEXTURE9> m_mapTextures;
	LPDIRECT3DTEXTURE9 CreateTextureFromFile(const data_types::String& imagePath);
};

} // namespace graphics