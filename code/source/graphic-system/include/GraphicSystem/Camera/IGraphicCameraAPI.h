#pragma once
#include "Core/DataTypes/Box.h"

namespace graphics::camera
{

class IGraphicCameraAPI
{
public:
	virtual core::BoxF GetRenderBoundary() const = 0;
};

} // namespace graphics
