#pragma once
#include "IGraphicSystem.h"
#include "FileSystem/IFileSystem.h"
#include "GraphicSystem/Graphics/GraphicsWrapper.h"
#include "Core/Identifiers/APIMode.h"
#include "DataTypes/SpriteState.h"
#include "DataTypes/AnimationState.h"
#include "Core/DataTypes/Flag.h"
#include <memory>
#include <Windows.h>
#include <map>
#include <optional>

namespace graphics
{

class GraphicsSystem final: public IGraphicsSystem
{
public:
	using InitParams = GraphicsWrapper::InitParams;
	GraphicsSystem(std::weak_ptr<files::IFileSystem> i_fileSystem);
	~GraphicsSystem();
	void Initialize(const InitParams& i_initParams);

	// Inherited via IGraphicsSystem
	std::weak_ptr<SpriteState> RegisterDraw(
		const ids::SpriteId i_spriteId, 
		const ids::RenderLayer i_renderLayer = ids::RenderLayer::Default
	) override;
	void DeregisterDraw(
		std::weak_ptr<SpriteState> i_spriteState
	) override;
	std::weak_ptr<AnimationState> RegisterDraw(
		const ids::AnimationId i_animationId, 
		const ids::RenderLayer i_renderLayer = ids::RenderLayer::Default
	) override;
	void DeregisterDraw(
		std::weak_ptr<AnimationState> i_animationState
	) override;
	void SetSpriteRenderLayer(
		const SpriteState::Id i_spriteStateId,
		const ids::RenderLayer i_oldRenderLayer,
		const ids::RenderLayer i_newRenderLayer
	) override;
	void SetAnimationRenderLayer(
		const AnimationState::Id i_animationStateId,
		const ids::RenderLayer i_oldRenderLayer,
		const ids::RenderLayer i_newRenderLayer
	) override;

private:
	using MapSrpiteStates = std::map<SpriteState::Id, std::shared_ptr<SpriteState>>;
	using MapAnimationStates = std::map<AnimationState::Id, std::shared_ptr<AnimationState>>;

	struct RenderStateContainer
	{
		MapSrpiteStates spriteStates;
		MapAnimationStates animationStates;
	};

	std::weak_ptr<files::IFileSystem> m_fileSystem;
	std::unique_ptr<GraphicsWrapper> m_graphicsWrapper;
	std::map<ids::RenderLayer, RenderStateContainer> m_mapRenderStateContainers;

	SpriteState GenerateSpriteState();
	AnimationState GenerateAnimationState();

	uint64_t GenerateId();
	uint64_t m_countId = 0;

	void InitRenderStateContainers();
	data_types::Flag m_initRenderStateContainersFlag;
};

} // namespace graphics