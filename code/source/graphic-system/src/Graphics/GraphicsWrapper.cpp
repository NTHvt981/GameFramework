#include "GraphicSystem/Graphics/GraphicsWrapper.h"
#include "D9Graphics.h"
#include "NoGraphics.h"
#include <assert.h>

namespace graphics
{

GraphicsWrapper::GraphicsWrapper()
{
}

GraphicsWrapper::~GraphicsWrapper()
{
	m_graphics.release();
}

void GraphicsWrapper::Initialize(const InitParams& i_initParams)
{
	switch (i_initParams.apiMode)
	{
	case ids::APIMode::D3D9:
	{
		assert(i_initParams.optHwnd.has_value());
		const HWND hwnd = i_initParams.optHwnd.value();
		m_graphics = std::make_unique<D9Graphics>(hwnd);
		break;
	}
	default:
		m_graphics = std::make_unique<NoGraphics>();
		break;
	}
}

} // namespace graphics