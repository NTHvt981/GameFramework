#pragma once
#include "API/ITileGraphicAPI.h"
#include "API/ISpriteGraphicAPI.h"
#include "API/IAnimationGraphicAPI.h"
#include "API/IViewportGraphicAPI.h"
#include "Core/DataTypes/Box.h"
#include "Core/DataTypes/Duration.h"

namespace graphics
{

class IGraphicSystem:	public ISpriteGraphicAPI,
						public IAnimationGraphicAPI,
						public ITileGraphicAPI,
						public IViewportGraphicAPI
{
public:
	virtual void Initialize() = 0;
	virtual void LoadTextures() = 0;
	virtual void Shutdown() = 0;

	virtual void PreRender(const core::Duration& dt) = 0;
	virtual void Render(const core::Duration& dt) = 0;
	virtual void PostRender(const core::Duration& dt) = 0;

	virtual void SetRenderFilter(const core::BoxF i_boundary) = 0;
	virtual void RemoveRenderFilter() = 0;
};

} // namespace graphics