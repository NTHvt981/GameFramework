#pragma once

#include "../Constraints.h"
#include "../GameObject/GameObject.h"

struct CollisionEvent
{
	LPGameObject object;
	Vector normal;
};

