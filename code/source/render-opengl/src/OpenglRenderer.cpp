#include "NoRenderer.h"
#include "Core/DataTypes/Flag.h"

#include <assert.h>

namespace graphics
{

NoRenderer::NoRenderer()
{
}

NoRenderer::~NoRenderer()
{
}

void NoRenderer::Draw(const DrawParams& i_drawParams)
{
}

ids::APIMode NoRenderer::GetAPIMode() const
{
	return ids::APIMode::NoAPIMode;
}

void NoRenderer::LoadTexture(
	const ids::TextureId i_textureId, 
	const core::String i_textureFilePath)
{
}

} // namespace graphics