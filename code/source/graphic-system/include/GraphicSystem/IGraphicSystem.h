#pragma once
#include "APIs/ITileGraphicAPI.h"
#include "APIs/ISpriteGraphicAPI.h"
#include "APIs/IAnimationGraphicAPI.h"
#include "GraphicSystem/Renderers/RendererWrapper.h"

namespace graphics
{

class IGraphicSystem:	public ISpriteGraphicAPI,
						public IAnimationGraphicAPI,
						public ITileGraphicAPI
{
public:
	using InitParams = RendererWrapper::InitParams;
	virtual void Initialize(const InitParams& i_initParams) = 0;
	virtual void Render() = 0;
};

} // namespace graphics