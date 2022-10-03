#pragma once
#include "ITransformComponent.h"
#include "Core/Identifiers/SpriteId.h"
#include <memory>

namespace graphics
{
class ISpriteGraphicAPI;
struct SpriteState;
namespace database
{
class IGraphicDatabaseAPI;
} // namespace database
} // namespace graphics

namespace logic
{

static constexpr core::ComponentKey sk_spriteComponentKey = "SpriteComponent";

class SpriteComponent final: public ITransformComponent
{
public:
	SpriteComponent(
		std::weak_ptr<graphics::ISpriteGraphicAPI> i_spriteGraphicAPI,
		std::weak_ptr<const graphics::database::IGraphicDatabaseAPI> i_graphicDatabaseAPI
	);
	~SpriteComponent();
	
	void SetPosition(core::Vector2F i_position) override;
	core::Vector2F GetPosition() const override;
	void Register() override;
	void Deregister() override;

	void SetSprite(const core::SpriteId i_spriteId);

private:
	std::weak_ptr<graphics::ISpriteGraphicAPI> m_spriteGraphicAPI;
	std::weak_ptr<const graphics::database::IGraphicDatabaseAPI> m_graphicDatabaseAPI;
	std::shared_ptr<graphics::SpriteState> m_spriteState;
	bool isRegistered = false;
};

} // namespace logic