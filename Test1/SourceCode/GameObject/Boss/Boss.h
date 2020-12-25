#pragma once

#include "../Enemies/Enemy.h"
#include "../Physic.h"
#include "../../Constraints.h"

#include "../../Library/SpriteLibrary.h"
#include "../../Unit/Sprite.h"
#include "../../Unit/Animation.h"

#include "BossArm.h"
#include "BossHand.h"

#include "../StaticObjects/Explosion.h"
#include "../../Debug/Utils.h"

#define BOSS_MOVE_SLOW 1
#define BOSS_MOVE_NORMAL 1.5
#define BOSS_MOVE_FAST 2

#define BOSS_NORMAL 0
#define BOSS_DEFEAT 1

#define BOSS_HEALTH 15

class CBoss : public CEnemy
{
private:
	LPAnimation animation;

	int width, height;

	const Vector leftHandPivot = Vector(-30, -8);
	const Vector rightHandPivot = Vector(30, -8);

	CBossHand *leftHand;
	CBossHand *rightHand;

	Vector localPosition = Vector(0, 0);
	Vector localGoalPosition = Vector(0, 0);
	const float range = 50;

	vector<pair<Vector, float>> movementMatrix;
	int movementIndex = 0;

	/// <summary>
	/// FOR DEBUG
	/// </summary>
	vector<Vector> armMovementMatrix;
	int rightArmIndex = 0;

	int state = BOSS_NORMAL;
	DWORD effectCountUp = 0;
	DWORD effectWaitTime = 15;

public:
	CBoss();
	void Update(DWORD dt);
	void Render();
	void SetCenter(float _x, float _y);

	void GetAllCollisionBoxes(list<LPCollisionBox> &listCo);

	void SetGoalPosition(float x, float y);
	Vector GetLocalPosition();

	void InflictDamage(int dam);
	int GetHealth();
	bool IsDefeat();

public:
	void HandleMovement(DWORD dt);
	bool HasReachGoal();
	void Reset();

private:
	void NormalState(DWORD dt);
	void DefeatState(DWORD dt);
};

