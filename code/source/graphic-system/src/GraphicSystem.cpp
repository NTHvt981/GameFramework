#include "GraphicSystem/GraphicSystem.h"
#include "Core/Math/Math.h"
#include "Core/Helpers/BoxHelper.h"

namespace graphics
{

////////////////////////////////////////////////////////////////////////////////

GraphicSystem::GraphicSystem(
    std::shared_ptr<INativeGraphicAPI> i_renderAPI,
    std::shared_ptr<database::IGraphicDatabaseAPI> i_databaseAPI)
    : m_nativeGraphicAPI(std::move(i_renderAPI))
    , m_databaseAPI(i_databaseAPI)
{
    InitLayerSpriteStateIds();
}

////////////////////////////////////////////////////////////////////////////////

GraphicSystem::~GraphicSystem()
{
    m_nativeGraphicAPI.reset();
    m_databaseAPI.reset();
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::Initialize()
{
    m_nativeGraphicAPI->Initialize();
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::LoadTextures()
{
    for (const core::TextureId id : core::TextureIdIterators())
    {
        const Texture texture = m_databaseAPI->GetTexture(id);
        m_nativeGraphicAPI->LoadTexture(id, texture.filePath);
    }
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::Shutdown()
{
    m_nativeGraphicAPI->Shutdown();
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::PreRender(const uint64_t dt)
{
    for (auto& [animationStateId, animationState] : m_allAnimationStates)
    {
        ProccessAnimationState(animationState, dt);
    }
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::Render(const uint64_t dt)
{
    for (const core::RenderLayer renderLayer : core::RenderLayerIterators())
    {
        for (const SpriteState::Id spriteStateId : m_mapLayerSpriteStateIds[renderLayer])
        {
            std::shared_ptr<SpriteState> spriteState = GetSpriteState(spriteStateId);
            std::shared_ptr<const SpriteDef> spriteDef = spriteState->spriteDef.lock();
            if (CheckRenderConditions(spriteState))
            {
                DrawSprite(spriteState);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::PostRender(const uint64_t dt)
{

}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::SetRenderFilter(const core::BoxF i_boundary)
{
    m_renderFilter = i_boundary;
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::RemoveRenderFilter()
{
    m_renderFilter.reset();
}

////////////////////////////////////////////////////////////////////////////////

std::weak_ptr<SpriteState> GraphicSystem::RegisterSprite(
    const core::SpriteId i_spriteId,
    const core::RenderLayer i_renderLayer)
{
    std::shared_ptr<SpriteState> result = std::make_shared<SpriteState>(GenerateSpriteState());
    InsertSpriteState(result);
    return result;
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::DeregisterSprite(const SpriteState::Id i_spriteStateId)
{
    std::shared_ptr<SpriteState> spriteState = GetSpriteState(i_spriteStateId);
    RemoveSpriteState(spriteState);
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::SetSpriteRenderLayer(
    const SpriteState::Id i_spriteStateId,
    const core::RenderLayer i_renderLayer)
{
    std::shared_ptr<SpriteState> spriteState = GetSpriteState(i_spriteStateId);
    const core::RenderLayer oldRenderLayer = spriteState->renderLayer;

    SpriteStateIds& oldIds = m_mapLayerSpriteStateIds[oldRenderLayer];
    SpriteStateIds& newIds = m_mapLayerSpriteStateIds[i_renderLayer];

    oldIds.erase(oldIds.find(i_spriteStateId));
    newIds.emplace(i_spriteStateId);
}

////////////////////////////////////////////////////////////////////////////////

// when system register animation, it also register spriteRef with same id
std::weak_ptr<AnimationState> GraphicSystem::RegisterAnimation(
    const core::AnimationId i_animationId, 
    const core::RenderLayer i_renderLayer)
{
    std::shared_ptr<AnimationState> result = std::make_shared<AnimationState>(GenerateAnimationState());
    InsertAnimationState(result);
    return result;
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::DeregisterAnimation(const AnimationState::Id i_animationStateId)
{
    std::shared_ptr<AnimationState> spriteState = GetAnimationState(i_animationStateId);
    RemoveAnimationState(spriteState);
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::SetAnimationRenderLayer(
    const AnimationState::Id i_animationStateId,
    const core::RenderLayer i_renderLayer)
{
    SetSpriteRenderLayer(i_animationStateId, i_renderLayer);
}

////////////////////////////////////////////////////////////////////////////////

SpriteState GraphicSystem::GenerateSpriteState()
{
    SpriteState state(m_idGenerator.Generate());
    return state;
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::InsertSpriteState(std::shared_ptr<SpriteState> i_spriteState)
{
    const SpriteState::Id id = i_spriteState->id;
    m_allSpriteStates[id] = i_spriteState;

    const core::RenderLayer renderLayer = i_spriteState->renderLayer;
    m_mapLayerSpriteStateIds[renderLayer].emplace(id);
}

////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<SpriteState> GraphicSystem::GetSpriteState(const SpriteState::Id i_spriteStateId) const
{
    return m_allSpriteStates.at(i_spriteStateId);
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::RemoveSpriteState(std::shared_ptr<SpriteState> i_spriteState)
{
    const core::RenderLayer renderLayer = i_spriteState->renderLayer;
    const SpriteState::Id id = i_spriteState->id;

    SpriteStateIds& layer = m_mapLayerSpriteStateIds[renderLayer];
    auto it = layer.find(id);
    if (it != layer.end())
    {
        layer.erase(it);
    }

    m_allSpriteStates.try_emplace(id, nullptr);
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::DrawSprite(std::shared_ptr<const SpriteState> i_spriteState)
{
    std::shared_ptr<const SpriteDef> spriteDef = i_spriteState->spriteDef.lock();
    std::shared_ptr<const Texture> textureDef = spriteDef->textureRef.lock();
    INativeGraphicAPI::DrawParams drawParams;

    drawParams.position = i_spriteState->position;
    drawParams.alpha = i_spriteState->alpha;
    drawParams.boundary = spriteDef->boundary;
    drawParams.origin = spriteDef->origin;
    drawParams.textureId = textureDef->id;

    m_nativeGraphicAPI->Draw(drawParams);
}

////////////////////////////////////////////////////////////////////////////////

AnimationState GraphicSystem::GenerateAnimationState()
{
    AnimationState animationstate(m_idGenerator.Generate());

    SpriteState spriteState(animationstate.id);
    animationstate.spriteStateRef = std::make_unique<SpriteState>(spriteState);

    return animationstate;
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::InsertAnimationState(std::shared_ptr<AnimationState> i_animationState)
{
    m_allAnimationStates[i_animationState->id] = i_animationState;
    std::shared_ptr<SpriteState> spriteState = i_animationState->spriteStateRef;
    InsertSpriteState(spriteState);
}

////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<AnimationState> GraphicSystem::GetAnimationState(const AnimationState::Id i_animationStateId) const
{
    return m_allAnimationStates.at(i_animationStateId);
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::RemoveAnimationState(std::shared_ptr<AnimationState> i_animationState)
{
    RemoveSpriteState(i_animationState->spriteStateRef);
    const AnimationState::Id id = i_animationState->id;
    m_allSpriteStates.try_emplace(id, nullptr);
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::ProccessAnimationState(std::shared_ptr<AnimationState> i_animationState, const uint64_t dt)
{
    if (i_animationState->pause)
    {
        return;
    }

    uint64_t& currentFrameIndex = i_animationState->currentFrameIndex;
    uint64_t& currentFrameTime = i_animationState->currentFrameTime;
    auto animationDef = i_animationState->animationDef.lock();
    
    uint64_t newFrameTime = currentFrameTime + dt;
    const AnimationFrameDef& currentFrame = animationDef->frames[currentFrameIndex];
    if (newFrameTime >= currentFrame.timeSpan)
    {
        currentFrameTime = newFrameTime - currentFrame.timeSpan;
        currentFrameIndex++;
        auto frameSize = animationDef->frames.size();
        if (currentFrameIndex >= frameSize)
        {
            if (!i_animationState->loop)
            {
                return;
            }

            currentFrameIndex = currentFrameIndex - frameSize;
            i_animationState->sig_onAnimationFinished.Emit();
        }

        const AnimationFrameDef& newFrame = animationDef->frames[currentFrameIndex];
        i_animationState->spriteStateRef->spriteDef = newFrame.spriteRef;
    }
    else
    {
        currentFrameTime = newFrameTime;
    }
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::InitLayerSpriteStateIds()
{
    for (const core::RenderLayer renderLayer : core::RenderLayerIterators())
    {
        m_mapLayerSpriteStateIds.try_emplace(renderLayer, std::set<SpriteState::Id>());
    }
}

////////////////////////////////////////////////////////////////////////////////

bool GraphicSystem::CheckRenderConditions(std::shared_ptr<const SpriteState> i_spriteState) const
{
    const bool isVisible = i_spriteState->visible;
    return isVisible && CheckRenderFilter(i_spriteState);
}

////////////////////////////////////////////////////////////////////////////////

bool GraphicSystem::CheckRenderFilter(std::shared_ptr<const SpriteState> i_spriteState) const
{
    if (m_renderFilter.has_value())
    {
        const core::BoxI64 spriteDefBoundary = i_spriteState->spriteDef.lock()->boundary;
        return core::IsOverlap(core::ToFloat(spriteDefBoundary), m_renderFilter.value());
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace graphics