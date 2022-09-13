#include "NoGraphics.h"
#include "Core/DataTypes/Flag.h"

#include <assert.h>

namespace graphics
{

NoGraphics::NoGraphics()
{
}

NoGraphics::~NoGraphics()
{
}

void NoGraphics::Draw(const DrawParams& i_drawParams)
{
}

void NoGraphics::LoadTexture(
	const ids::TextureId i_textureId, 
	const data_types::String i_textureFilePath)
{
}

} // namespace graphics