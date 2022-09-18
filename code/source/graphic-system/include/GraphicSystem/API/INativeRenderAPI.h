#pragma once
#include "GraphicSystem/DataTypes/SpriteState.h"
#include "GraphicSystem/DataTypes/Texture.h"
#include "Core/Identifiers/TextureId.h"
#include "Core/Identifiers/APIMode.h"
#include "Core/DataTypes/Box.h"
#include "Core/DataTypes/Vector2.h"
#include "Core/DataTypes/String.h"
#include <optional>

namespace graphics
{

class INativeRenderAPI
{
public:
	virtual void Initialize() = 0;
	virtual void LoadTexture(const ids::TextureId i_textureId, const core::String i_textureFilePath) = 0;
	struct DrawParams
	{
		ids::TextureId textureId;
		core::Vector2F position{0, 0};
		core::Vector2F origin{ 0, 0 };
		core::BoxI64 boundary{ 0, 0, 0, 0 };
		float alpha = 1;
		float scale = 1;

		struct CameraParams
		{
			core::Vector2F position{ 0, 0 };
			core::BoxI64 boundary{ 0, 0, 0, 0 };
		};
		std::optional<CameraParams> optCameraParams;
	};
	virtual void Draw(const DrawParams& i_drawParams) = 0;
	virtual ids::APIMode GetAPIMode() const = 0;
	virtual void Shutdown() = 0;
};

} // namespace graphics
