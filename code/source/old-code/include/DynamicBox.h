#pragma once

#include "Constraints.h"
#include "Collision.h"
#include "CollisionBox.h"
#include "CollisionEvent.h"
#include "Entity.h"

//Advance collision box, have an update function that get called when entity finish moving
class CDynamicBox: public CCollisionBox
{
protected:
	LPEntity entity;
	Vector localPosition;
	Vector size;

public:
	void Update();
	void Follow(float x, float y);
	void CalculateCollision(Vector& velocity,
		std::list<CollisionEvent>& events);
	CDynamicBox(LPEntity _entity, 
		float _localX=0, float _localY=0, float width=0, float height=0
	);

	//void Reset
	void ResetCoCollisionBoxes(std::list<LPCollisionBox> newCoCollisionBoxes);
	Vector GetSize();
	Vector GetLocalPosition();
};

