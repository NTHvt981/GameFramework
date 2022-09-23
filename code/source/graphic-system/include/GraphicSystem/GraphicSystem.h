#pragma once
#include "IGraphicSystem.h"
#include "Database/IGraphicDatabaseAPI.h"
#include "Core/Identifiers/APIMode.h"
#include "Core/GameClock/IGameClock.h"
#include "Core/DataTypes/Flag.h"
#include "DataTypes/SpriteState.h"
#include "DataTypes/AnimationState.h"
#include "API/INativeRenderAPI.h"
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
	void SetRenderFilter(const core::BoxI64 i_boundary) override;
	void RemoveRenderFilter() override;

	// Inherited via ISpriteGraphicAPI
	std::weak_ptr<SpriteState> RegisterSprite(
		const ids::SpriteId i_spriteId, 
		const ids::RenderLayer i_renderLayer = ids::RenderLayer::Default
	) override;
	void DeregisterSprite(
		const SpriteState::Id i_spriteStateId
	) override;
	void SetSpriteRenderLayer(
		const SpriteState::Id i_spriteStateId,
		const ids::RenderLayer i_renderLayer
	) override;

	// Inherited via IAnimationGraphicAPI
	std::weak_ptr<AnimationState> RegisterAnimation(
		const ids::AnimationId i_animationId, 
		const ids::RenderLayer i_renderLayer = ids::RenderLayer::Default
	) override;
	void DeregisterAnimation(
		const AnimationState::Id i_animationStateId
	) override;
	void SetAnimationRenderLayer(
		const AnimationState::Id i_animationStateId,
		const ids::RenderLayer i_renderLayer
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
	std::map<ids::RenderLayer, SpriteStateIds> m_mapLayerSpriteStateIds;
	std::map<SpriteState::Id, std::shared_ptr<SpriteState>> m_allSpriteStates;
	std::map<AnimationState::Id, std::shared_ptr<AnimationState>> m_allAnimationStates;

	std::shared_ptr<database::IGraphicDatabaseAPI> m_databaseAPI;
	std::shared_ptr<INativeGraphicAPI> m_nativeGraphicAPI;

	uint64_t GenerateId();
	uint64_t m_countId = 0;

	void InitLayerSpriteStateIds();

	bool CheckFilter(const core::BoxI64 i_renderBoundary) const;
	std::optional<core::BoxI64> m_filterBound;
};

} // namespace graphics