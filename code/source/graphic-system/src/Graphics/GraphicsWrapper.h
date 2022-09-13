#pragma once
#include "IGraphics.h"
#include "GraphicSystem/DataTypes/GraphicSystemInitParam.h"
#include <Windows.h>
#include <memory>

namespace graphics
{

class GraphicsWrapper final: public IGraphics
{
public:
	GraphicsWrapper();
	void Initialize(const GraphicSystemInitParam& i_initParams);

private:
	std::unique_ptr<IGraphics> m_graphics;
};

} // namespace graphics