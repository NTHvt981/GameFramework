#pragma once

#include "Constraints.h"
#include "Entity.h"

#include "Sprite.h"
#include "SpriteLibrary.h"

#define ARM_MOVE_SLOW 1.5
#define ARM_MOVE_NORMAL 2
#define ARM_MOVE_FAST 3
#define ARM_MOVE_VERY_FAST 4

class CBossArm: public CEntity
{
private:
	CBossArm* child;
	bool isTheEnd = false;

	int64_t width, height;
	float range;

	LPSprite sprite = NULL;

	Vector localPosition = Vector(0, 0);
	Vector localGoalPosition = Vector(0, 0);

	float speed = ARM_MOVE_NORMAL;

public:
	CBossArm(CBossArm* _armBeforeIt, int64_t sprId, float range);
	void GetAllCollisionBoxes(std::list<LPCollisionBox>& listCo);

protected:
	void Move(DWORD dt);

public:
	void SetGoalPosition(float x, float y);
	Vector GetLocalPosition();
	void MoveCallFromParent(DWORD dt, float _x, float _y);
	void MoveCallFromBoss(DWORD dt, float _x, float _y);
	void Update(DWORD dt);
	void Render();
	void SetPosition(float _x, float _y);
};

