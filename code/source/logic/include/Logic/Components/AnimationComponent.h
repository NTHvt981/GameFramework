#pragma once
#include "Component.h"
#include "GraphicSystem/API/IAnimationGraphicAPI.h"
#include "GraphicSystem/DataTypes/AnimationState.h"
#include "GraphicSystem/Database/IGraphicDatabaseAPI.h"
#include "Core/Signals/Connection.h"
#include <memory>

namespace logic
{

class AnimationComponent final : public Component
{
public:
	AnimationComponent(
		std::weak_ptr<graphics::IAnimationGraphicAPI> i_animationGraphicAPI,
		std::weak_ptr<const graphics::database::IGraphicDatabaseAPI> i_graphicDatabaseAPI,
		core::AnimationId i_animationId
	);
	~AnimationComponent();

	// Inherited via Component
	void SetPosition(const core::Vector2F& i_position) override;
	core::Vector2F GetPosition() const override;
	void Register() override;
	void Deregister() override;

	void SetVisible(const bool i_visible);
	bool GetVisible() const;
	void SetAnimation(const core::AnimationId i_animationId);
	core::AnimationId GetAnimationId() const;

	signals::Signal<> sig_onAnimationFinished;
private:
	void OnAnimationFinished();

	std::weak_ptr<graphics::IAnimationGraphicAPI> m_animationGraphicAPI;
	std::weak_ptr<const graphics::database::IGraphicDatabaseAPI> m_graphicDatabaseAPI;
	core::AnimationId m_animationId;
	std::shared_ptr<graphics::AnimationState> m_animationState;
	bool isRegistered = false;
	
	signals::Connection<> m_onAnimationFinishedCon;
};

} // namespace logic