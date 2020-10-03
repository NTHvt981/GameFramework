#pragma once

#include "../Constraints.h"
#include "CollisionBox.h"
#include "../GameObject/Entity.h"

//Advance collision box, have an update function that get called when entity finish moving
class CDynamicBox: public CCollisionBox
{
protected:
	LPEntity entity;
	Vector localPosition;
	Vector size;

public:
	void Update();
	CDynamicBox(LPEntity _entity, float _localX, float _localY, float width, float height);
};

