#pragma once
#include "GraphicSystem/API/INativeGraphicAPI.h"
#include "Core/Identifiers/APIMode.h"
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9core.h>
#include <memory>
#include <unordered_map>

namespace graphics
{

class Direct9GraphicAPI final : public INativeGraphicAPI
{
public:
	Direct9GraphicAPI(const HWND i_hwnd);
	~Direct9GraphicAPI();

	// Inherited via IRenderer
	void Initialize() override;
	void LoadTexture(
		const core::TextureId i_textureId, 
		const core::String i_textureFilePath
	) override;
	void Draw(const DrawParams& i_drawParams) override;
	core::APIMode GetAPIMode() const override;
	void Shutdown() override;

private:
	void DrawAbsolute();
	void DrawRelative();

	const HWND m_hwnd;
	LPDIRECT3D9 m_direct3D9 = nullptr;
	LPDIRECT3DDEVICE9 m_direct3DDevice9 = nullptr;
	LPDIRECT3DSURFACE9 m_backBuffer = nullptr;
	LPD3DXSPRITE m_spriteHandler = nullptr;

	std::unordered_map<core::TextureId, LPDIRECT3DTEXTURE9> m_mapTextures;
	LPDIRECT3DTEXTURE9 CreateTextureFromFile(const core::String& imagePath);
};

} // namespace graphics