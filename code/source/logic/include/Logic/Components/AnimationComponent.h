#pragma once
#include "ITransformComponent.h"
#include "GraphicSystem/API/IAnimationGraphicAPI.h"
#include "GraphicSystem/DataTypes/AnimationState.h"
#include "GraphicSystem/Database/IGraphicDatabaseAPI.h"
#include "Core/Signals/Connection.h"
#include "Core/DataTypes/Ref.h"
#include <memory>

namespace logic
{

static constexpr core::ComponentKey sk_animationComponentKey = "AnimationComponent";

class AnimationComponent final : public ITransformComponent
{
public:
	AnimationComponent(
		std::shared_ptr<graphics::IAnimationGraphicAPI> i_animationGraphicAPI,
		std::weak_ptr<const graphics::database::IGraphicDatabaseAPI> i_graphicDatabaseAPI
	);
	~AnimationComponent();

	void SetPosition(core::Vector2F i_position) override;
	core::Vector2F GetPosition() const override;
	void Register() override;
	void Deregister() override;

	void SetAnimation(const core::AnimationId i_animationId);
	core::AnimationId GetAnimationId() const;

	signals::Signal<> sig_onAnimationFinished;
private:
	void OnAnimationFinished();

	core::Ref<graphics::IAnimationGraphicAPI> m_animationGraphicAPI;
	std::weak_ptr<const graphics::database::IGraphicDatabaseAPI> m_graphicDatabaseAPI;
	std::shared_ptr<graphics::AnimationState> m_animationState;
	bool isRegistered = false;
	
	signals::Connection<> m_onAnimationFinishedCon;
};

} // namespace logic