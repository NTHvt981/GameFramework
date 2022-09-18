#include "GraphicSystem/GraphicSystem.h"
#include "Core/Identifiers/FileId.h"

namespace graphics
{

GraphicSystem::GraphicSystem(
    std::weak_ptr<core::logic::IGameClock> i_gameClock,
    std::weak_ptr<files::IFileSystem> i_fileSystem,
    std::shared_ptr<INativeRenderAPI> i_renderAPI)
    : m_fileSystem(i_fileSystem)
    , m_renderAPI(std::move(i_renderAPI))
{
    InitLayerSpriteStateIds();
    
    std::shared_ptr<core::logic::IGameClock> gameClock = i_gameClock.lock();
    m_onPreRenderCon = gameClock->sig_onPreRender.Connect(std::bind(&GraphicSystem::OnPreRender, this, std::placeholders::_1));
    m_onRenderCon = gameClock->sig_onRender.Connect(std::bind(&GraphicSystem::OnRender, this, std::placeholders::_1));
    m_onPostRenderCon = gameClock->sig_onPostRender.Connect(std::bind(&GraphicSystem::OnPostRender, this, std::placeholders::_1));
}

GraphicSystem::~GraphicSystem()
{
    m_renderAPI.reset();
    m_fileSystem.reset();
}

void GraphicSystem::Initialize()
{
    m_renderAPI->Initialize();
    LoadTexture(ids::TextureId::BlackScreen);
    LoadTexture(ids::TextureId::Boss);
    LoadTexture(ids::TextureId::CollisionDebug);
    LoadTexture(ids::TextureId::Enemies);
    LoadTexture(ids::TextureId::Item);
    LoadTexture(ids::TextureId::Opening);
    LoadTexture(ids::TextureId::OtherObjects);
    LoadTexture(ids::TextureId::Player);
    LoadTexture(ids::TextureId::PlayerHealth);
    LoadTexture(ids::TextureId::Rollout);
}

void GraphicSystem::Shutdown()
{
    m_renderAPI->Shutdown();
}

std::weak_ptr<SpriteState> GraphicSystem::RegisterSprite(
    const ids::SpriteId i_spriteId, 
    const ids::RenderLayer i_renderLayer)
{
    std::shared_ptr<SpriteState> result = std::make_shared<SpriteState>(GenerateSpriteState());
    InsertSpriteState(result);
    return result;
}

void GraphicSystem::DeregisterSprite(const SpriteState::Id i_spriteStateId)
{
    std::shared_ptr<SpriteState> spriteState = GetSpriteState(i_spriteStateId);
    RemoveSpriteState(spriteState);
}

void GraphicSystem::SetSpriteRenderLayer(
    const SpriteState::Id i_spriteStateId,
    const ids::RenderLayer i_renderLayer)
{
    std::shared_ptr<SpriteState> spriteState = GetSpriteState(i_spriteStateId);
    const ids::RenderLayer oldRenderLayer = spriteState->renderLayer;

    SpriteStateIds& oldIds = m_mapLayerSpriteStateIds[oldRenderLayer];
    SpriteStateIds& newIds = m_mapLayerSpriteStateIds[i_renderLayer];
    
    oldIds.erase(oldIds.find(i_spriteStateId));
    newIds.emplace(i_spriteStateId);
}

// when system register animation, it also register sprite with same id
std::weak_ptr<AnimationState> GraphicSystem::RegisterAnimation(
    const ids::AnimationId i_animationId, 
    const ids::RenderLayer i_renderLayer)
{
    std::shared_ptr<AnimationState> result = std::make_shared<AnimationState>(GenerateAnimationState());
    InsertAnimationState(result);
    return result;
}

void GraphicSystem::DeregisterAnimation(const AnimationState::Id i_animationStateId)
{
    std::shared_ptr<AnimationState> spriteState = GetAnimationState(i_animationStateId);
    RemoveAnimationState(spriteState);
}

void GraphicSystem::SetAnimationRenderLayer(
    const AnimationState::Id i_animationStateId,
    const ids::RenderLayer i_renderLayer)
{
    SetSpriteRenderLayer(i_animationStateId, i_renderLayer);
}

SpriteState GraphicSystem::GenerateSpriteState()
{
    SpriteState state(GenerateId());
    return state;
}

void GraphicSystem::InsertSpriteState(std::shared_ptr<SpriteState> i_spriteState)
{
    const SpriteState::Id id = i_spriteState->id;
    m_allSpriteStates[id] = i_spriteState;
    
    const ids::RenderLayer renderLayer = i_spriteState->renderLayer;
    m_mapLayerSpriteStateIds[renderLayer].emplace(id);
}

std::shared_ptr<SpriteState> GraphicSystem::GetSpriteState(const SpriteState::Id i_spriteStateId) const
{
    return m_allSpriteStates.at(i_spriteStateId);
}

void GraphicSystem::RemoveSpriteState(std::shared_ptr<SpriteState> i_spriteState)
{
    const ids::RenderLayer renderLayer = i_spriteState->renderLayer;
    const SpriteState::Id id = i_spriteState->id;
    
    SpriteStateIds& layer = m_mapLayerSpriteStateIds[renderLayer];
    auto it = layer.find(id);
    if (it != layer.end())
    {
        layer.erase(it);
    }

    m_allSpriteStates.try_emplace(id, nullptr);
}

void GraphicSystem::DrawSprite(const SpriteState::Id i_spriteStateId)
{
    std::shared_ptr<const SpriteState> spriteState = GetSpriteState(i_spriteStateId);
    const INativeRenderAPI::DrawParams drawParams = ToDrawParams(spriteState);
    m_renderAPI->Draw(drawParams);
}

INativeRenderAPI::DrawParams GraphicSystem::ToDrawParams(std::shared_ptr<const SpriteState> i_spriteState)
{
    std::shared_ptr<const SpriteDef> spriteDef = i_spriteState->spriteDef.lock();
    std::shared_ptr<const Texture> textureDef = spriteDef->texture.lock();
    INativeRenderAPI::DrawParams result;
    
    result.position = i_spriteState->position;
    result.alpha = i_spriteState->alpha;
    result.boundary = spriteDef->boundary;
    result.origin = spriteDef->origin;
    result.textureId = textureDef->id;

    return result;
}

AnimationState GraphicSystem::GenerateAnimationState()
{
    AnimationState animationstate(GenerateId());

    SpriteState spriteState(animationstate.id);
    animationstate.spriteStateRef = std::make_unique<SpriteState>(spriteState);

    return animationstate;
}

void GraphicSystem::InsertAnimationState(std::shared_ptr<AnimationState> i_animationState)
{
    m_allAnimationStates[i_animationState->id] = i_animationState;
    std::shared_ptr<SpriteState> spriteState = i_animationState->spriteStateRef;
    InsertSpriteState(spriteState);
}

std::shared_ptr<AnimationState> GraphicSystem::GetAnimationState(const AnimationState::Id i_animationStateId) const
{
    return m_allAnimationStates.at(i_animationStateId);
}

void GraphicSystem::RemoveAnimationState(std::shared_ptr<AnimationState> i_animationState)
{
    RemoveSpriteState(i_animationState->spriteStateRef);
    const AnimationState::Id id = i_animationState->id;
    m_allSpriteStates.try_emplace(id, nullptr);
}

uint64_t GraphicSystem::GenerateId()
{
    m_countId++;
    return m_countId;
}

void GraphicSystem::InitLayerSpriteStateIds()
{
    for (const ids::RenderLayer renderLayer : ids::RenderLayerIterator())
    {
        m_mapLayerSpriteStateIds.try_emplace(renderLayer, std::set<SpriteState::Id>());
    }
}

void GraphicSystem::LoadTexture(const ids::TextureId i_textureId)
{
    std::shared_ptr<files::IFileSystem> fileSystem = m_fileSystem.lock();

    core::String path;
    switch (i_textureId)
    {
    case ids::TextureId::BlackScreen:
        path = fileSystem->GetFileDirectory(ids::FileId::BlackScreenTexture);
        break;
    case ids::TextureId::Boss:
        path = fileSystem->GetFileDirectory(ids::FileId::BossTexture);
        break;
    case ids::TextureId::CollisionDebug:
        path = fileSystem->GetFileDirectory(ids::FileId::CollisionDebugTexture);
        break;
    case ids::TextureId::Enemies:
        path = fileSystem->GetFileDirectory(ids::FileId::EnemiesTexture);
        break;
    case ids::TextureId::Item:
        path = fileSystem->GetFileDirectory(ids::FileId::ItemTexture);
        break;
    case ids::TextureId::Opening:
        path = fileSystem->GetFileDirectory(ids::FileId::OpeningTexture);
        break;
    case ids::TextureId::OtherObjects:
        path = fileSystem->GetFileDirectory(ids::FileId::OtherObjectsTexture);
        break;
    case ids::TextureId::Player:
        path = fileSystem->GetFileDirectory(ids::FileId::PlayerTexture);
        break;
    case ids::TextureId::PlayerHealth:
        path = fileSystem->GetFileDirectory(ids::FileId::PlayerHealthTexture);
        break;
    case ids::TextureId::Rollout:
        path = fileSystem->GetFileDirectory(ids::FileId::RolloutTexture);
        break;
    case ids::TextureId::COUNT:
        assert(false);
        break;
    }

    m_renderAPI->LoadTexture(i_textureId, path);
}

void GraphicSystem::OnPreRender(const uint64_t dt)
{
}

void GraphicSystem::OnRender(const uint64_t dt)
{
    for (const ids::RenderLayer renderLayer : ids::RenderLayerIterator())
    {
        for (const SpriteState::Id spriteStateId : m_mapLayerSpriteStateIds[renderLayer])
        {
            DrawSprite(spriteStateId);
        }
    }
}

void GraphicSystem::OnPostRender(const uint64_t dt)
{
}

} // namespace graphics