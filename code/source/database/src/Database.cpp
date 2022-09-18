#include "Database/Database.h"

namespace database
{
std::weak_ptr<const graphics::Texture> Database::GetTextureRef(const ids::TextureId i_textureId)
{
}
const graphics::Texture Database::GetTexture(const ids::TextureId i_textureId)
{
}
std::weak_ptr<const graphics::SpriteDef> Database::GetSpriteRef(const ids::SpriteId i_spriteId)
{
}
const graphics::SpriteDef Database::GetSprite(const ids::SpriteId i_spriteId)
{
}
std::weak_ptr<const graphics::AnimationDef> Database::GetAnimationRef(const ids::AnimationId i_animationId)
{
}
const graphics::AnimationDef Database::GetAnimation(const ids::AnimationId i_animationId)
{
}
} // namespace database