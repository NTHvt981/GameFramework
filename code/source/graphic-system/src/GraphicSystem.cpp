#include "GraphicSystem/GraphicSystem.h"

namespace graphics
{

GraphicsSystem::GraphicsSystem(std::weak_ptr<files::IFileSystem> i_fileSystem)
    : m_fileSystem(i_fileSystem)
    , m_graphicsWrapper(std::make_unique<GraphicsWrapper>())
{
    InitRenderStateContainers();
}

GraphicsSystem::~GraphicsSystem()
{
    m_graphicsWrapper.release();
    m_fileSystem.reset();
}

void GraphicsSystem::Initialize(const InitParams& i_initParams)
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

void GraphicsSystem::SetSpriteRenderLayer(
    const SpriteState::Id i_spriteStateId,
    const ids::RenderLayer i_oldRenderLayer,
    const ids::RenderLayer i_newRenderLayer)
{
    RenderStateContainer& oldContainer = m_mapRenderStateContainers.at(i_oldRenderLayer);

    assert(oldContainer.spriteStates.contains(i_spriteStateId));
    std::shared_ptr<SpriteState> state = std::move(oldContainer.spriteStates[i_spriteStateId]);

    RenderStateContainer& newContainer = m_mapRenderStateContainers.at(i_newRenderLayer);

    assert(!newContainer.spriteStates.contains(i_spriteStateId));
    newContainer.spriteStates.try_emplace(i_spriteStateId, state);
}

void GraphicsSystem::SetAnimationRenderLayer(
    const AnimationState::Id i_animationStateId,
    const ids::RenderLayer i_oldRenderLayer,
    const ids::RenderLayer i_newRenderLayer)
{
    RenderStateContainer& oldContainer = m_mapRenderStateContainers.at(i_oldRenderLayer);

    assert(oldContainer.animationStates.contains(i_animationStateId));
    std::shared_ptr<AnimationState> state = std::move(oldContainer.animationStates[i_animationStateId]);

    RenderStateContainer& newContainer = m_mapRenderStateContainers.at(i_newRenderLayer);

    assert(!newContainer.animationStates.contains(i_animationStateId));
    newContainer.animationStates.try_emplace(i_animationStateId, state);
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