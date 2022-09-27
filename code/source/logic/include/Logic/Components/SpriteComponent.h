#pragma once
#include "ITransformComponent.h"
#include "GraphicSystem/API/ISpriteGraphicAPI.h"
#include "GraphicSystem/DataTypes/SpriteState.h"
#include <memory>

namespace logic
{

/// <summary>
/// A component wrap sprite
/// </summary>
class SpriteComponent final: public ITransformComponent
{
public:
	SpriteComponent(
		std::weak_ptr<graphics::ISpriteGraphicAPI> i_spriteGraphicAPI,
		const core::SpriteId i_spriteId
	);
	~SpriteComponent();
	
	void SetPosition(const core::Vector2F& i_position) override;
	core::Vector2F GetPosition() const override;
	void Register() override;
	void Deregister() override;

	void SetVisible(const bool i_visible);
	bool GetVisible() const;

private:
	std::weak_ptr<graphics::ISpriteGraphicAPI> m_spriteGraphicAPI;
	const core::SpriteId m_spriteId;
	std::shared_ptr<graphics::SpriteState> m_spriteState;
	bool isRegistered = false;
};

} // namespace logic