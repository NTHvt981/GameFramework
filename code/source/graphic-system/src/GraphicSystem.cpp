#include "GraphicSystem/GraphicSystem.h"

namespace graphics
{

GraphicsSystem::GraphicsSystem(std::weak_ptr<files::IFileSystem> i_fileSystem)
    : m_fileSystem(i_fileSystem)
    , m_graphicsWrapper(std::make_unique<GraphicsWrapper>())
{
    InitRenderStateContainers();
}

void GraphicsSystem::Initialize(const GraphicSystemInitParam& i_initParams)
{
    m_graphicsWrapper->Initialize(i_initParams);
}

std::weak_ptr<SpriteState> GraphicsSystem::RegisterDraw(
    const ids::SpriteId i_spriteId, 
    const ids::RenderLayer i_renderLayer)
{
    RenderStateContainer& container = m_mapRenderStateContainers.at(i_renderLayer);

    std::shared_ptr<SpriteState> result = std::make_shared<SpriteState>(GenerateSpriteState());
    container.spriteStates.emplace(result->id, result);

    return result;
}

void GraphicsSystem::DeregisterDraw(std::weak_ptr<SpriteState> i_spriteState)
{
    std::shared_ptr<SpriteState> lockPtr = i_spriteState.lock();

    for (auto& [layerId, container] : m_mapRenderStateContainers)
    {
        MapSrpiteStates& mapStates = container.spriteStates;
        mapStates.try_emplace(lockPtr->id, nullptr);
    }
}

std::weak_ptr<AnimationState> GraphicsSystem::RegisterDraw(
    const ids::AnimationId i_animationId, 
    const ids::RenderLayer i_renderLayer)
{
    RenderStateContainer& container = m_mapRenderStateContainers.at(i_renderLayer);

    std::shared_ptr<AnimationState> result = std::make_shared<AnimationState>(GenerateAnimationState());
    container.animationStates.emplace(result->id, result);
    return result;
}

void GraphicsSystem::DeregisterDraw(const std::weak_ptr<AnimationState> i_animationState)
{
    std::shared_ptr<AnimationState> lockPtr = i_animationState.lock();

    for (auto& [layerId, container] : m_mapRenderStateContainers)
    {
        MapAnimationStates& mapStates = container.animationStates;
        mapStates.try_emplace(lockPtr->id, nullptr);
    }
}

void GraphicsSystem::SetRenderLayer(const SpriteState::Id i_spriteStateId, const ids::RenderLayer i_renderLayer)
{
    // TODO: Implement this
    //ids::RenderLayer oldContainerId = ids::RenderLayer::COUNT;
    //for (auto& [layerId, container] : m_mapRenderStateContainers)
    //{
    //    MapAnimationStates& mapStates = container.animationStates;
    //    if (mapStates)
    //}

    //assert(oldContainerId != ids::RenderLayer::COUNT);

    //RenderStateContainer& newContainer = m_mapRenderStateContainers.at(i_renderLayer);
}

SpriteState GraphicsSystem::GenerateSpriteState()
{
    SpriteState state;
    state.id = GenerateId();
    return state;
}

AnimationState GraphicsSystem::GenerateAnimationState()
{
    AnimationState state;
    state.id = GenerateId();
    return state;
}

uint64_t GraphicsSystem::GenerateId()
{
    m_countId++;
    return m_countId;
}

void GraphicsSystem::InitRenderStateContainers()
{
    m_initRenderStateContainersFlag.Set();
    uint64_t count = static_cast<uint64_t>(ids::RenderLayer::COUNT);
    for (size_t i = 0; i < count; i++)
    {
        const ids::RenderLayer layerId = static_cast<ids::RenderLayer>(i);
        m_mapRenderStateContainers.try_emplace(layerId, RenderStateContainer{});
    }
}

} // namespace graphics