#pragma once
#include "GraphicSystem/Renderers/IRenderer.h"
#include "Core/Identifiers/APIMode.h"

namespace graphics
{

class NoRenderer final : public IRenderer
{
public:
	NoRenderer();
	~NoRenderer();

	// Inherited via IRenderer
	void LoadTexture(
		const ids::TextureId i_textureId, 
		const core::String i_textureFilePath
	) override;
	void Draw(const DrawParams& i_drawParams) override;
	ids::APIMode GetAPIMode() const override;
};

} // namespace graphics