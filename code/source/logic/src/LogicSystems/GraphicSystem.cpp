#include "Logic/LogicSystems/GraphicSystem.h"
#include "Core/DataTypes/Texture.h"
#include "Core/DataTypes/SpriteState.h"
#include "Core/DataTypes/AnimationState.h"
#include "Core/Math/Math.h"
#include "Core/Helpers/BoxHelper.h"

namespace graphics
{

////////////////////////////////////////////////////////////////////////////////

GraphicSystem::GraphicSystem(
    std::unique_ptr<INativeGraphicAPI> i_nativeGraphicAPI,
    std::shared_ptr<const database::IGraphicDatabaseAPI> i_databaseAPI)
    : m_nativeGraphicAPI(std::move(i_nativeGraphicAPI))
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

void GraphicSystem::PreRender(const core::Duration& dt)
{
    UpdateAnimationStates(dt);
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::Render(const core::Duration& dt)
{
    StartDraw();

    for (const core::RenderLayer renderLayer : core::RenderLayerIterators())
    {
        for (const SpriteState::Id spriteStateId : m_mapLayerSpriteStateIds[renderLayer])
        {
            std::shared_ptr<SpriteState> spriteState = GetSpriteState(spriteStateId);
            std::shared_ptr<const SpriteDef> spriteDef = spriteState->spriteDef.lock();
            DrawSprite(spriteState);
        }
    }

    EndDraw();
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::PostRender(const core::Duration& dt)
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

void GraphicSystem::RegisterSprite(std::shared_ptr<SpriteState> i_spriteState)
{
    const SpriteState::Id id = i_spriteState->id;
    m_allSpriteStates[id] = i_spriteState;

    const core::RenderLayer renderLayer = i_spriteState->renderLayer;
    m_mapLayerSpriteStateIds[renderLayer].emplace(id);
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

// when system register animation, it also register spriteDefRef with same id
void GraphicSystem::RegisterAnimation(std::shared_ptr<AnimationState> i_animationState)
{
    InsertAnimationState(i_animationState);
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

void GraphicSystem::StartDraw()
{
    m_nativeGraphicAPI->StartDraw();
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::EndDraw()
{
    m_nativeGraphicAPI->EndDraw();
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::SetViewportSize(const core::SizeF& i_viewportSize)
{
    m_nativeGraphicAPI->SetViewportSize(i_viewportSize);
}

////////////////////////////////////////////////////////////////////////////////

void GraphicSystem::SetViewportPosition(const core::Vector2F& i_viewportPosition)
{
    m_nativeGraphicAPI->SetViewportPosition(i_viewportPosition);
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
    drawParams.textureBoundary = spriteDef->textureBoundary;
    drawParams.origin = spriteDef->origin;
    drawParams.textureId = textureDef->id;

    m_nativeGraphicAPI->Draw(drawParams);
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

void GraphicSystem::UpdateAnimationStates(const core::Duration& dt)
{
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

bool GraphicSystem::CheckRenderFilter(std::shared_ptr<const SpriteState> i_spriteState) const
{
    if (m_renderFilter.has_value())
    {
        const core::BoxI64 spriteDefBoundary = i_spriteState->spriteDef.lock()->textureBoundary;
        return core::IsOverlap(
            core::CastBox<int64_t, float>(spriteDefBoundary), 
            m_renderFilter.value()
        );
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////

SpriteState::Id GraphicSystem::GenerateSpriteStateId()
{
    return m_idGenerator.Generate();
}

////////////////////////////////////////////////////////////////////////////////

AnimationState::Id GraphicSystem::GenerateAnimationStateId()
{
    return m_idGenerator.Generate();
}

////////////////////////////////////////////////////////////////////////////////

} // namespace graphics