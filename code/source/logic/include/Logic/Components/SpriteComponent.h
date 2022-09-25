#pragma once
#include "IComponent.h"
#include "GraphicSystem/API/ISpriteGraphicAPI.h"
#include "GraphicSystem/DataTypes/SpriteState.h"
#include <memory>

namespace logic
{

/// <summary>
/// A component wrap sprite
/// </summary>
class SpriteComponent final: public IComponent
{
public:
	SpriteComponent(
		std::weak_ptr<graphics::ISpriteGraphicAPI> i_spriteGraphicAPI,
		const core::SpriteId i_spriteId
	);
	~SpriteComponent();
	
	// Inherited via IComponent
	void SetPosition(const core::Vector2F& i_position) override;
	core::Vector2F GetPosition() const override;
	void Register() override;
	void Deregister() override;

private:
	std::weak_ptr<graphics::ISpriteGraphicAPI> m_spriteGraphicAPI;
	const core::SpriteId m_spriteId;
	std::shared_ptr<graphics::SpriteState> m_spriteState;
	bool isRegistered = false;
};

} // namespace logic