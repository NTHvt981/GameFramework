#pragma once
#include "GraphicSystem/API/INativeRenderAPI.h"
#include "Core/Identifiers/APIMode.h"

namespace graphics
{

class DebugRenderAPI final : public INativeRenderAPI
{
public:
	DebugRenderAPI();
	~DebugRenderAPI();

	// Inherited via IRenderer
	void Initialize() override;
	void LoadTexture(
		const ids::TextureId i_textureId, 
		const core::String i_textureFilePath
	) override;
	void Draw(const DrawParams& i_drawParams) override;
	ids::APIMode GetAPIMode() const override;
	void Shutdown() override;
};

} // namespace graphics