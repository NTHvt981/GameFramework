#pragma once
#include "GraphicSystem/Graphics/IGraphics.h"
#include "GraphicSystem/IGraphicSystem.h"
#include "Core/Identifiers/APIMode.h"
#include <Windows.h>
#include <memory>

namespace graphics
{

class GraphicsWrapper
{
public:
	struct InitParams
	{
		ids::APIMode apiMode;
		std::optional<HWND> optHwnd;
	};
	GraphicsWrapper();
	~GraphicsWrapper();
	void Initialize(const InitParams& i_initParams);

private:
	std::unique_ptr<IGraphics> m_graphics;
};

} // namespace graphics