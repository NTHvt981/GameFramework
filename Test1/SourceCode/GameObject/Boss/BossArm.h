#pragma once

#include "../../Constraints.h"
#include "../Entity.h"

#include "../../Unit/Sprite.h"
#include "../../Library/SpriteLibrary.h"

#define ARM_MOVE_SLOW 1.5
#define ARM_MOVE_FAST 2.5
#define ARM_MOVE_VERY_FAST 3

class CBossArm: public CEntity
{
private:
	CBossArm* child;
	bool isTheEnd = false;

	int width, height;
	float range;

	LPSprite sprite = NULL;

	Vector localPosition = Vector(0, 0);
	Vector localGoalPosition = Vector(0, 0);

	float speed = ARM_MOVE_SLOW;

public:
	CBossArm(CBossArm* _armBeforeIt, int sprId, float range);

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

