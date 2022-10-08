#pragma once
#include "ITransformComponent.h"
#include "Core/Signals/Connection.h"
#include "Core/Identifiers/AnimationId.h"
#include "Core/DataTypes/Size.h"
#include <memory>

namespace graphics
{
class IAnimationGraphicAPI;
struct AnimationState;
namespace database
{
class IGraphicDatabaseAPI;
} // namespace database
} // namespace graphics

namespace logic
{

static constexpr core::ComponentKey sk_animationComponentKey = "AnimationComponent";

class AnimationComponent final : public ITransformComponent
{
public:
	AnimationComponent(
		std::shared_ptr<graphics::IAnimationGraphicAPI> i_animationGraphicAPI,
		std::shared_ptr<const graphics::database::IGraphicDatabaseAPI> i_graphicDatabaseAPI
	);
	~AnimationComponent();

	void SetPosition(core::Vector2F i_position) override;
	core::Vector2F GetPosition() const override;
	void Register() override;
	void Deregister() override;

	void SetAnimation(const core::AnimationId i_animationId);
	core::AnimationId GetAnimationId() const;
	bool IsLoop();
	void SetLoop(bool i_value);
	core::SizeI64 GetSpriteSizeInFrame(uint64_t i_frameIndex);

	signals::Signal<> sig_onAnimationFinished;
private:
	void OnAnimationFinished();

	graphics::IAnimationGraphicAPI& m_animationGraphicAPI;
	const graphics::database::IGraphicDatabaseAPI& m_graphicDatabaseAPI;
	std::shared_ptr<graphics::AnimationState> m_animationState;
	bool isRegistered = false;
	
	signals::Connection<> m_onAnimationFinishedCon;
};

} // namespace logic