#pragma once
#include "ITransformComponent.h"
#include "Core/Signals/Connection.h"
#include "Core/Identifiers/AnimationId.h"
#include "Core/DataTypes/Size.h"
#include "Core/DataTypes/Duration.h"
#include "Core/APIs/IAnimationGraphicAPI.h"
#include "Logic/Databases/IGraphicDatabaseAPI.h"
#include <memory>

namespace logic
{

static constexpr core::ComponentKey sk_animationComponentKey = "AnimationComponent";

class AnimationComponent final : public ITransformComponent
{
public:
	AnimationComponent(
		std::shared_ptr<core::IAnimationGraphicAPI> i_animationGraphicAPI,
		std::shared_ptr<const IGraphicDatabaseAPI> i_graphicDatabaseAPI
	);
	~AnimationComponent();

	void SetPosition(core::Vector2F i_position) override;
	core::Vector2F GetPosition() const override;
	void Register() override;
	void Deregister() override;

	void Update(const core::Duration& dt);

	void SetAnimation(const core::AnimationId i_animationId);
	core::AnimationId GetAnimationId() const;
	bool IsLoop();
	void SetLoop(bool i_value);
	float GetSpeed() const;
	void SetSpeed(float i_speed);
	core::SizeI64 GetSpriteSizeInFrame(uint64_t i_frameIndex);

	signals::Signal<> sig_onAnimationFinished;
private:
	void OnAnimationFinished();

	core::IAnimationGraphicAPI& m_animationGraphicAPI;
	const IGraphicDatabaseAPI& m_graphicDatabaseAPI;
	std::shared_ptr<core::AnimationState> m_animationState;
	bool m_isRegistered = false;
	
	signals::Connection<> m_onAnimationFinishedCon;
};

} // namespace logic