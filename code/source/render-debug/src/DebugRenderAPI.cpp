#include "RenderDebug/DebugRenderAPI.h"
#include "Core/DataTypes/Flag.h"
#include <assert.h>

namespace graphics
{

core::Flag s_initFlag;
core::Flag s_shutdownFlag;

DebugRenderAPI::DebugRenderAPI()
{
	
}

DebugRenderAPI::~DebugRenderAPI()
{
	Shutdown();
}

void DebugRenderAPI::Initialize()
{
	if (s_initFlag.IsSet())
	{
		return;
	}
	s_initFlag.Set();
}

void DebugRenderAPI::LoadTexture(
	const ids::TextureId i_textureId,
	const core::String i_textureFilePath)
{

}

void DebugRenderAPI::Draw(const DrawParams& i_drawParams)
{
}

ids::APIMode DebugRenderAPI::GetAPIMode() const
{
	return ids::APIMode::NoAPIMode;
}

void DebugRenderAPI::Shutdown()
{
	if (s_shutdownFlag.IsSet())
	{
		return;
	}
	s_shutdownFlag.Set();
}

} // namespace graphics