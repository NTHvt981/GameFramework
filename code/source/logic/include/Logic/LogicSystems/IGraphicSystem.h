#pragma once
#include "Core/APIs/ITileGraphicAPI.h"
#include "Core/APIs/ISpriteGraphicAPI.h"
#include "Core/APIs/IAnimationGraphicAPI.h"
#include "Core/APIs/IViewportGraphicAPI.h"
#include "Core/DataTypes/Box.h"
#include "Core/DataTypes/Duration.h"

namespace logic
{

class IGraphicSystem:	public core::ISpriteGraphicAPI,
						public core::IAnimationGraphicAPI,
						public core::ITileGraphicAPI,
						public core::IViewportGraphicAPI
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

} // namespace logic