#pragma once
#include "GraphicSystem/DataTypes/SpriteState.h"
#include "GraphicSystem/DataTypes/Texture.h"
#include "Core/Identifiers/TextureId.h"
#include "Core/DataTypes/Box.h"
#include "Core/DataTypes/Vector2.h"
#include "Core/DataTypes/String.h"
#include <optional>

namespace graphics
{

class IRenderer
{
public:
	virtual void LoadTexture(const ids::TextureId i_textureId, const data_types::String i_textureFilePath) = 0;

	struct DrawParams
	{
		ids::TextureId textureId;
		data_types::Vector2F position{0, 0};
		data_types::Vector2F origin{ 0, 0 };
		data_types::BoxI64 boundary{ 0, 0, 0, 0 };
		float alpha = 1;
		float scale = 1;

		struct CameraParams
		{
			data_types::Vector2F position{ 0, 0 };
			data_types::BoxI64 boundary{ 0, 0, 0, 0 };
		};
		std::optional<CameraParams> optCameraParams;
	};
	virtual void Draw(const DrawParams& i_drawParams) = 0;
};

} // namespace graphics
