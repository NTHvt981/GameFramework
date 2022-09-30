#pragma once
#include "IComponent.h"
#include <memory>

namespace logic
{

static constexpr core::ComponentKey sk_enemyTagComponentKey = "EnemyTagComponent";
static constexpr core::ComponentKey sk_playerTagComponentKey = "PlayerTagComponent";
static constexpr core::ComponentKey sk_bullerTagComponentKey = "BulletTagComponent";

class ITagComponent: public IComponent
{
public:
	void Register() override {};
	void Deregister() override {};
};

class EnemyTagComponent : public ITagComponent {};
class PlayerTagComponent : public ITagComponent {};
class BulletTagComponent : public ITagComponent {};

} // namespace logic