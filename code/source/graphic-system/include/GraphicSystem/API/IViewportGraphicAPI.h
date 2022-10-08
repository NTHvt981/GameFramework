#pragma once
#include "Core/DataTypes/Size.h"
#include "Core/DataTypes/Vector2.h"

namespace graphics
{

class IViewportGraphicAPI
{
public:
	virtual void SetWindowSize(const core::SizeF i_screenSize) = 0;
	virtual void SetViewportSize(const core::SizeF& i_viewportSize) = 0;
	virtual void SetViewportPosition(const core::Vector2F& i_viewportPosition) = 0;
};

} // namespace graphics