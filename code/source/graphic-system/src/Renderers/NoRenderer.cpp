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

void NoRenderer::LoadTexture(
	const ids::TextureId i_textureId, 
	const data_types::String i_textureFilePath)
{
}

} // namespace graphics