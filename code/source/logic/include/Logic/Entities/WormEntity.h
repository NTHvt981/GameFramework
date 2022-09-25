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
	const char* GetName() const override
	{
		return sk_WormEntity;
	}

	std::weak_ptr<KinematicBodyComponent> body;
	std::weak_ptr<KinematicBodyComponent> detectorBody;
	std::weak_ptr<AnimationComponent> moveLeftAnimation;
	std::weak_ptr<AnimationComponent> moveRightAnimation;
};

} // namespace logic