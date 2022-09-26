#pragma once
#include "Entity.h"
#include "Logic/Components/KinematicBodyComponent.h"
#include "Logic/Components/AnimationComponent.h"
#include <memory>

namespace logic
{

static const char* sk_WormEntity = "Worm";

struct WormEntity: public Entity
{
	using Entity::Entity;
	std::weak_ptr<KinematicBodyComponent> body;
	std::weak_ptr<KinematicBodyComponent> detectorBody;
	std::weak_ptr<AnimationComponent> animation;
};

} // namespace logic