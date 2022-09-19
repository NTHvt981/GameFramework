#include "GraphicDebug/DebugGraphicAPI.h"
#include "Core/DataTypes/Flag.h"
#include <assert.h>

namespace graphics
{

core::Flag s_initFlag;
core::Flag s_shutdownFlag;

DebugGraphicAPI::DebugGraphicAPI()
{
	
}

DebugGraphicAPI::~DebugGraphicAPI()
{
	Shutdown();
}

void DebugGraphicAPI::Initialize()
{
	if (s_initFlag.IsSet())
	{
		return;
	}
	s_initFlag.Set();
}

void DebugGraphicAPI::LoadTexture(
	const ids::TextureId i_textureId,
	const core::String i_textureFilePath)
{

}

void DebugGraphicAPI::Draw(const DrawParams& i_drawParams)
{
}

ids::APIMode DebugGraphicAPI::GetAPIMode() const
{
	return ids::APIMode::NoAPIMode;
}

void DebugGraphicAPI::Shutdown()
{
	if (s_shutdownFlag.IsSet())
	{
		return;
	}
	s_shutdownFlag.Set();
}

} // namespace graphics