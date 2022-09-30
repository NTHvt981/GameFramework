#pragma once
#include "Core/DataTypes/Box.h"
#include "Core/Signals/Signal.h"

namespace graphics::camera
{

class IGraphicCameraAPI
{
public:
	virtual core::BoxF GetRenderBoundary() const = 0;
};

} // namespace graphics
