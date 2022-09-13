#pragma once
#include <cstdint>

namespace ids
{

enum class FileId : uint64_t
{
	TextureDataXml,
	EnemiesTexture,
	PlayerTexture,
	PlayerHealthTexture,
	OtherObjectsTexture,
	BlackScreenTexture,
	BossTexture,
	OpeningTexture,
	RolloutTexture,
	ItemTexture,
	CollisionDebugTexture,
	COUNT // Special enum
};

} // namespace ids
