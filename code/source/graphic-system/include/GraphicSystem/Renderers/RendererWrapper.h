#pragma once
#include "GraphicSystem/Renderers/IRenderer.h"
#include "Core/Identifiers/APIMode.h"
#include <Windows.h>
#include <memory>

namespace graphics
{

class RendererWrapper final : public IRenderer
{
public:
	struct InitParams
	{
		ids::APIMode apiMode;
		std::optional<HWND> optHwnd;
	};
	RendererWrapper();
	~RendererWrapper();
	void Initialize(const InitParams& i_initParams);

	// Inherited via IRenderer
	void LoadTexture(
		const ids::TextureId i_textureId,
		const data_types::String i_textureFilePath
	) override;
	void Draw(const DrawParams& i_drawParams) override;

private:
	std::unique_ptr<IRenderer> m_renderer;
};

} // namespace graphics