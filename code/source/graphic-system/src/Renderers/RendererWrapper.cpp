#include "GraphicSystem/Renderers/RendererWrapper.h"
#include "D3D9Renderer.h"
#include "NoRenderer.h"
#include <assert.h>

namespace graphics
{

RendererWrapper::RendererWrapper()
{
}

RendererWrapper::~RendererWrapper()
{
	m_renderer.release();
}

void RendererWrapper::Initialize(const InitParams& i_initParams)
{
	switch (i_initParams.apiMode)
	{
	case ids::APIMode::D3D9:
	{
		assert(i_initParams.optHwnd.has_value());
		const HWND hwnd = i_initParams.optHwnd.value();
		m_renderer = std::make_unique<D3D9Renderer>(hwnd);
		break;
	}
	default:
		m_renderer = std::make_unique<NoRenderer>();
		break;
	}
}

void RendererWrapper::LoadTexture(const ids::TextureId i_textureId, const data_types::String i_textureFilePath)
{
	m_renderer->LoadTexture(i_textureId, i_textureFilePath);
}

void RendererWrapper::Draw(const DrawParams& i_drawParams)
{
	m_renderer->Draw(i_drawParams);
}

} // namespace graphics