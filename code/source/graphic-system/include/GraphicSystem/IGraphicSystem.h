#pragma once
#include "IGraphicAPI.h"
#include "GraphicSystem/Renderers/RendererWrapper.h"

namespace graphics
{

class IGraphicSystem: public IGraphicAPI
{
public:
	using InitParams = RendererWrapper::InitParams;
	virtual void Initialize(const InitParams& i_initParams) = 0;
	virtual void Render() = 0;
};

} // namespace graphics