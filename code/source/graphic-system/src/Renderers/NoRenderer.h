#pragma once
#include "GraphicSystem/Renderers/IRenderer.h"
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9core.h>
#include <memory>

namespace graphics
{

class NoRenderer final : public IRenderer
{
public:
	NoRenderer();
	~NoRenderer();

	// Inherited via IRenderer
	virtual void LoadTexture(
		const ids::TextureId i_textureId, 
		const data_types::String i_textureFilePath
	) override;
	virtual void Draw(const DrawParams& i_drawParams) override;
};

} // namespace graphics