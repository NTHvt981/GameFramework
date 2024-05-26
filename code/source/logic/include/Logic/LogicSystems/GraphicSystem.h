#pragma once
#include "IGraphicSystem.h"
#include "Logic/Databases/IGraphicDatabaseAPI.h"
#include "Core/Identifiers/APIMode.h"
#include "Core/GameClock/IGameClock.h"
#include "Core/DataTypes/Flag.h"
#include "Core/GameSetting/GameSetting.h"
#include "Core/Signals/Connection.h"
#include "Core/Generator/IncrementIdGenerator.h"
#include "Core/DataTypes/SpriteState.h"
#include "Core/DataTypes/AnimationState.h"
#include "Core/APIs/INativeGraphicAPI.h"
#include <memory>
#include <optional>
#include <Windows.h>
#include <map>
#include <set>

namespace logic
{

class GraphicSystem final: public IGraphicSystem
{
public:
	GraphicSystem(
		std::unique_ptr<core::INativeGraphicAPI> i_nativeGraphicAPI,
		std::shared_ptr<const graphics::database::IGraphicDatabaseAPI> i_databaseAPI
	);
	~GraphicSystem();
	// Inherited via IGraphicSystem
	void Initialize() override;
	void LoadTextures() override;
	void Shutdown() override;
	void PreRender(const core::Duration& dt) override;
	void Render(const core::Duration& dt) override;
	void PostRender(const core::Duration& dt) override;
	void SetRenderFilter(const core::BoxF i_boundary) override;
	void RemoveRenderFilter() override;

	// Inherited via IViewportGraphicAPI
	void SetViewportSize(const core::SizeF& i_viewportSize) override;
	void SetViewportPosition(const core::Vector2F& i_viewportPosition) override;

	// Inherited via ISpriteGraphicAPI
	core::SpriteState::Id GenerateSpriteStateId() override;
	void RegisterSprite(std::shared_ptr<core::SpriteState> i_spriteState) override;
	void DeregisterSprite(const core::SpriteState::Id i_spriteStateId) override;
	void SetSpriteRenderLayer(
		const core::SpriteState::Id i_spriteStateId,
		const core::RenderLayer i_renderLayer
	) override;

	// Inherited via IAnimationGraphicAPI
	core::AnimationState::Id GenerateAnimationStateId() override;
	void RegisterAnimation(std::shared_ptr<core::AnimationState> i_animationState) override;
	void DeregisterAnimation(
		const core::AnimationState::Id i_animationStateId
	) override;
	void SetAnimationRenderLayer(
		const core::AnimationState::Id i_animationStateId,
		const core::RenderLayer i_renderLayer
	) override;
private:
	void StartDraw();
	void EndDraw();

	void InsertSpriteState(std::shared_ptr<core::SpriteState> i_spriteState);
	std::shared_ptr<core::SpriteState> GetSpriteState(const core::SpriteState::Id i_spriteStateId) const;
	void RemoveSpriteState(std::shared_ptr<core::SpriteState> i_spriteState);
	void DrawSprite(std::shared_ptr<const core::SpriteState> i_spriteState);

	void InsertAnimationState(std::shared_ptr<core::AnimationState> i_animationState);
	std::shared_ptr<core::AnimationState> GetAnimationState(const core::AnimationState::Id i_animationStateId) const;
	void RemoveAnimationState(std::shared_ptr<core::AnimationState> i_animationState);
	void UpdateAnimationStates(const core::Duration& dt);

	using SpriteStateIds = std::set<core::SpriteState::Id>;
	std::map<core::RenderLayer, SpriteStateIds> m_mapLayerSpriteStateIds;
	std::map<core::SpriteState::Id, std::shared_ptr<core::SpriteState>> m_allSpriteStates;
	std::map<core::AnimationState::Id, std::shared_ptr<core::AnimationState>> m_allAnimationStates;

	std::shared_ptr<const graphics::database::IGraphicDatabaseAPI> m_databaseAPI;
	std::unique_ptr<core::INativeGraphicAPI> m_nativeGraphicAPI;
	core::IncrementIdGenerator m_idGenerator;

	void InitLayerSpriteStateIds();

	bool CheckRenderFilter(std::shared_ptr<const core::SpriteState> i_spriteState) const;
	std::optional<core::BoxF> m_renderFilter;

};

} // namespace logic