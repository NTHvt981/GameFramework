#pragma once
#include "API/ITileGraphicAPI.h"
#include "API/ISpriteGraphicAPI.h"
#include "API/IAnimationGraphicAPI.h"

namespace graphics
{

class IGraphicSystem:	public ISpriteGraphicAPI,
						public IAnimationGraphicAPI,
						public ITileGraphicAPI
{
public:
	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;
};

} // namespace graphics