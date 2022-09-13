#pragma once
#include "IGraphicSystem.h"
#include "FileSystem/IFileSystem.h"
#include "Core/Identifiers/APIMode.h"
#include "Core/Interfaces/IRenderable.h"
#include "DataTypes/SpriteState.h"
#include "DataTypes/AnimationState.h"
#include "Core/DataTypes/Flag.h"
#include <memory>
#include <Windows.h>
#include <map>
#include <optional>

namespace graphics
{

class GraphicSystem final: public IGraphicSystem
{
public:
	GraphicSystem(std::weak_ptr<files::IFileSystem> i_fileSystem);
	~GraphicSystem();
	// Inherited via IGraphicSystem
	void Initialize(const IGraphicSystem::InitParams& i_initParams) override;
	void Render() override;

	// Inherited via IGraphicAPI
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
	std::unique_ptr<RendererWrapper> m_graphicsWrapper;
	std::map<ids::RenderLayer, RenderStateContainer> m_mapRenderStateContainers;

	SpriteState GenerateSpriteState();
	AnimationState GenerateAnimationState();

	uint64_t GenerateId();
	uint64_t m_countId = 0;

	void InitRenderStateContainers();
	data_types::Flag m_initRenderStateContainersFlag;

	void LoadTexture(const ids::TextureId i_textureId);
};

} // namespace graphics