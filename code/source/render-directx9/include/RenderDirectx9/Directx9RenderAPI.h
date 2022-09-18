#pragma once
#include "GraphicSystem/API/INativeRenderAPI.h"
#include "Core/Identifiers/APIMode.h"
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9core.h>
#include <memory>
#include <unordered_map>

namespace graphics
{

class Directx9RenderAPI final : public INativeRenderAPI
{
public:
	Directx9RenderAPI(const HWND i_hwnd);
	~Directx9RenderAPI();

	// Inherited via IRenderer
	void Initialize() override;
	void LoadTexture(
		const ids::TextureId i_textureId, 
		const core::String i_textureFilePath
	) override;
	void Draw(const DrawParams& i_drawParams) override;
	ids::APIMode GetAPIMode() const override;
	void Shutdown() override;

private:
	const HWND m_hwnd;
	LPDIRECT3D9 m_direct3D9;
	LPDIRECT3DDEVICE9 m_direct3DDevice9;
	LPDIRECT3DSURFACE9 m_backBuffer;
	LPD3DXSPRITE m_spriteHandler;

	std::unordered_map<ids::TextureId, LPDIRECT3DTEXTURE9> m_mapTextures;
	LPDIRECT3DTEXTURE9 CreateTextureFromFile(const core::String& imagePath);
};

} // namespace graphics