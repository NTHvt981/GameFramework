#pragma once

#include "Constraints.h"
#include "Entity.h"

#include "BossArm.h"

#include "Sprite.h"
#include "SpriteLibrary.h"

class CBossHand : public CEntity
{
private:
	CBossArm* child;

	int64_t width, height;

	LPSprite sprite = NULL;

	const float range = 80;

	Vector localPosition = Vector(0, 0);
	Vector localGoalPosition = Vector(0, 0);

	float speed = ARM_MOVE_NORMAL;

	void setUpBossArm(int64_t parentId);

public:
	CBossHand(int64_t id);
	void GetAllCollisionBoxes(std::list<LPCollisionBox>& listCo);

	void SetGoalPosition(float x, float y);
	Vector GetLocalPosition();

public:
	void MoveCallFromBoss(DWORD dt, float _x, float _y);
	void Update(DWORD dt);
	void Render();
	void SetPosition(float _x, float _y);

private:
	void MoveAxis(float &cur, float &goal);

public:
	bool HasReachGoal();
};

