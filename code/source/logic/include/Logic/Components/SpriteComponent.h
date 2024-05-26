#pragma once
#include "ITransformComponent.h"
#include "Core/Identifiers/SpriteId.h"
#include "Core/APIs/ISpriteGraphicAPI.h"
#include "Logic/Databases/IGraphicDatabaseAPI.h"
#include "Core/DataTypes/SpriteState.h"
#include <memory>

namespace logic
{

static constexpr core::ComponentKey sk_spriteComponentKey = "SpriteComponent";

class SpriteComponent final: public ITransformComponent
{
public:
	SpriteComponent(
		std::shared_ptr<core::ISpriteGraphicAPI> i_spriteGraphicAPI,
		std::shared_ptr<const graphics::database::IGraphicDatabaseAPI> i_graphicDatabaseAPI
	);
	~SpriteComponent();
	
	void SetPosition(core::Vector2F i_position) override;
	core::Vector2F GetPosition() const override;
	void Register() override;
	void Deregister() override;

	void SetSprite(const core::SpriteId i_spriteId);

private:
	core::ISpriteGraphicAPI& m_spriteGraphicAPI;
	const graphics::database::IGraphicDatabaseAPI& m_graphicDatabaseAPI;
	std::shared_ptr<core::SpriteState> m_spriteState;
	bool isRegistered = false;
};

} // namespace logic