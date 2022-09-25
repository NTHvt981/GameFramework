#pragma once
#include "IComponent.h"
#include "GraphicSystem/API/IAnimationGraphicAPI.h"
#include "GraphicSystem/DataTypes/AnimationState.h"
#include "Core/Signals/Connection.h"
#include <memory>

namespace logic
{

class AnimationComponent final : public IComponent
{
public:
	AnimationComponent(
		std::weak_ptr<graphics::IAnimationGraphicAPI> i_animationGraphicAPI,
		const core::AnimationId i_animationId
	);
	~AnimationComponent();

	// Inherited via IComponent
	void SetPosition(const core::Vector2F& i_position) override;
	core::Vector2F GetPosition() const override;
	void Register() override;
	void Deregister() override;

	signals::Signal<> sig_onAnimationFinished;
private:
	void OnAnimationFinished();

	std::weak_ptr<graphics::IAnimationGraphicAPI> m_animationGraphicAPI;
	const core::AnimationId m_animationId;
	std::shared_ptr<graphics::AnimationState> m_animationState;
	bool isRegistered = false;
	
	signals::Connection<> m_onAnimationFinishedCon;
};

} // namespace logic