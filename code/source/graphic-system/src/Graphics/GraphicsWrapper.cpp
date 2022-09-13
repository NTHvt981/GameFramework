#include "GraphicsWrapper.h"
#include "D9Graphics.h"
#include <assert.h>

namespace graphics
{

GraphicsWrapper::GraphicsWrapper()
{
}

void GraphicsWrapper::Initialize(const GraphicSystemInitParam& i_initParams)
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
		throw("Invalid");
		break;
	}
}

} // namespace graphics