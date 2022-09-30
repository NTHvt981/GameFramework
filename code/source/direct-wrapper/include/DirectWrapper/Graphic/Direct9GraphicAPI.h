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
	void SetWindowSize(const core::SizeF i_screenSize) override;
	void SetDisplaySize(const core::SizeF i_displaySize) override;
	void SetDisplayPosition(const core::Vector2F i_displayPosition) override;
	void Draw(const DrawParams& i_drawParams) override;
	void StartDraw() override;
	void EndDraw() override;
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

	core::SizeF m_screenSize{ 0,0 };
	core::SizeF m_displaySize{ 0,0 };
	core::Vector2F m_displayPosition{ 0,0 };

	void ResetDrawMatrix();
	D3DXMATRIX m_drawMatrix;
};

} // namespace graphics