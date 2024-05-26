#pragma once
#include "Core/DataTypes/Size.h"
#include "Core/DataTypes/Vector2.h"

namespace core
{

class IViewportGraphicAPI
{
public:
	virtual void SetViewportSize(const core::SizeF& i_viewportSize) = 0;
	virtual void SetViewportPosition(const core::Vector2F& i_viewportPosition) = 0;
};

} // namespace core