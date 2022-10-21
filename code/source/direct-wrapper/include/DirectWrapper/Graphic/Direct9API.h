#pragma once
#include "GraphicSystem/API/INativeGraphicAPI.h"
#include "Core/Identifiers/APIMode.h"
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9core.h>
#include <memory>
#include <unordered_map>
#include <wrl/client.h>

namespace graphics
{

class Direct9API final : public INativeGraphicAPI
{
public:
	Direct9API(const HWND i_hwnd);
	~Direct9API();

	// Inherited via IRenderer
	void Initialize() override;
	void LoadTexture(
		const core::TextureId i_textureId, 
		const core::String i_textureFilePath
	) override;
	void SetViewportSize(const core::SizeF& i_viewportSize) override;
	void SetViewportPosition(const core::Vector2F& i_viewportPosition) override;
	void Draw(const DrawParams& i_drawParams) override;
	void StartDraw() override;
	void EndDraw() override;
	core::APIMode GetAPIMode() const override;
	void Shutdown() override;

private:
	void DrawAbsolute();
	void DrawRelative();

	const HWND m_hwnd;

	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	ComPtr<IDirect3D9> m_direct3D9 = nullptr;
	D3DPRESENT_PARAMETERS m_direct3DParams;
	ComPtr<IDirect3DDevice9> m_direct3DDevice9 = nullptr;
	ComPtr<IDirect3DSurface9> m_backBuffer = nullptr;
	ComPtr<ID3DXSprite> m_spriteHandler = nullptr;

	std::unordered_map<core::TextureId, ComPtr<IDirect3DTexture9>> m_mapTextures;
	ComPtr<IDirect3DTexture9> CreateTextureFromFile(const core::String& imagePath);

	core::SizeF m_backBufferSize{ 256, 224 };
	core::SizeF m_viewportSize{ 256, 224 };
	core::Vector2F m_viewportPosition{ 0,0 };

	void ResetDrawMatrix();
};

} // namespace graphics