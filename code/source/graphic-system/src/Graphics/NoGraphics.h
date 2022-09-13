#pragma once
#include "GraphicSystem/Graphics/IGraphics.h"
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9core.h>
#include <memory>

namespace graphics
{

class NoGraphics final : public IGraphics
{
public:
	NoGraphics();
	~NoGraphics();

	// Inherited via IGraphics
	virtual void LoadTexture(
		const ids::TextureId i_textureId, 
		const data_types::String i_textureFilePath
	) override;
	virtual void Draw(const DrawParams& i_drawParams) override;
};

} // namespace graphics