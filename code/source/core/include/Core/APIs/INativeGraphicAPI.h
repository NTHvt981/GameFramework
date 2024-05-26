#pragma once
#include "Core/Identifiers/TextureId.h"
#include "Core/Identifiers/DrawMode.h"
#include "Core/Identifiers/APIMode.h"
#include "Core/DataTypes/Box.h"
#include "Core/DataTypes/Size.h"
#include "Core/DataTypes/Vector2.h"
#include "Core/DataTypes/String.h"
#include <optional>

namespace core
{

struct SpriteState;
struct Texture;

class INativeGraphicAPI
{
public:
	virtual void Initialize() = 0;
	virtual void LoadTexture(const core::TextureId i_textureId, const core::String i_textureFilePath) = 0;
	struct DrawParams
	{
		TextureId textureId;
		Vector2F position{ 0, 0 };
		Vector2F origin{ 0, 0 };
		BoxI64 textureBoundary{ 0, 0, 0, 0 };
		float alpha = 1;
		float scale = 1;
		DrawMode drawMode;
	};
	virtual void SetViewportSize(const core::SizeF& i_viewportSize) = 0;
	virtual void SetViewportPosition(const core::Vector2F& i_viewportPosition) = 0;
	virtual void Draw(const DrawParams& i_drawParams) = 0;
	virtual void StartDraw() = 0;
	virtual void EndDraw() = 0;
	virtual APIMode GetAPIMode() const = 0;
	virtual void Shutdown() = 0;
};

} // namespace core
