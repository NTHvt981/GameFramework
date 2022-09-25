#pragma once
#include "IGraphicSystem.h"
#include "Database/IGraphicDatabaseAPI.h"
#include "Core/Identifiers/APIMode.h"
#include "Core/GameClock/IGameClock.h"
#include "Core/DataTypes/Flag.h"
#include "Core/Generator/IncrementIdGenerator.h"
#include "DataTypes/SpriteState.h"
#include "DataTypes/AnimationState.h"
#include "API/INativeGraphicAPI.h"
#include <memory>
#include <optional>
#include <Windows.h>
#include <map>
#include <set>

namespace graphics
{

class GraphicSystem final: public IGraphicSystem
{
public:
	GraphicSystem(
		std::shared_ptr<INativeGraphicAPI> i_renderAPI,
		std::shared_ptr<database::IGraphicDatabaseAPI> i_databaseAPI
	);
	~GraphicSystem();
	// Inherited via IGraphicSystem
	void Initialize() override;
	void LoadTextures() override;
	void Shutdown() override;
	void PreRender(const uint64_t dt) override;
	void Render(const uint64_t dt) override;
	void PostRender(const uint64_t dt) override;
	void SetRenderFilter(const core::BoxF i_boundary) override;
	void RemoveRenderFilter() override;

	// Inherited via ISpriteGraphicAPI
	std::weak_ptr<SpriteState> RegisterSprite(
		const core::SpriteId i_spriteId, 
		const core::RenderLayer i_renderLayer = core::RenderLayer::Default
	) override;
	void DeregisterSprite(
		const SpriteState::Id i_spriteStateId
	) override;
	void SetSpriteRenderLayer(
		const SpriteState::Id i_spriteStateId,
		const core::RenderLayer i_renderLayer
	) override;

	// Inherited via IAnimationGraphicAPI
	std::weak_ptr<AnimationState> RegisterAnimation(
		const core::AnimationId i_animationId, 
		const core::RenderLayer i_renderLayer = core::RenderLayer::Default
	) override;
	void DeregisterAnimation(
		const AnimationState::Id i_animationStateId
	) override;
	void SetAnimationRenderLayer(
		const AnimationState::Id i_animationStateId,
		const core::RenderLayer i_renderLayer
	) override;
private:
	SpriteState GenerateSpriteState();
	void InsertSpriteState(std::shared_ptr<SpriteState> i_spriteState);
	std::shared_ptr<SpriteState> GetSpriteState(const SpriteState::Id i_spriteStateId) const;
	void RemoveSpriteState(std::shared_ptr<SpriteState> i_spriteState);
	void DrawSprite(std::shared_ptr<const SpriteState> i_spriteState);

	AnimationState GenerateAnimationState();
	void InsertAnimationState(std::shared_ptr<AnimationState> i_animationState);
	std::shared_ptr<AnimationState> GetAnimationState(const AnimationState::Id i_animationStateId) const;
	void RemoveAnimationState(std::shared_ptr<AnimationState> i_animationState);
	void ProccessAnimationState(std::shared_ptr<AnimationState> i_animationState, const uint64_t dt);

	using SpriteStateIds = std::set<SpriteState::Id>;
	std::map<core::RenderLayer, SpriteStateIds> m_mapLayerSpriteStateIds;
	std::map<SpriteState::Id, std::shared_ptr<SpriteState>> m_allSpriteStates;
	std::map<AnimationState::Id, std::shared_ptr<AnimationState>> m_allAnimationStates;

	std::shared_ptr<database::IGraphicDatabaseAPI> m_databaseAPI;
	std::shared_ptr<INativeGraphicAPI> m_nativeGraphicAPI;
	core::IncrementIdGenerator m_idGenerator;

	void InitLayerSpriteStateIds();

	bool CheckRenderConditions(std::shared_ptr<const SpriteState> i_spriteState) const;
	bool CheckRenderFilter(std::shared_ptr<const SpriteState> i_spriteState) const;
	std::optional<core::BoxF> m_renderFilter;
};

} // namespace graphics