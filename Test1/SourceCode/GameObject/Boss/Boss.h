#pragma once

#include "../Enemies/Enemy.h"
#include "../Physic.h"
#include "../../Constraints.h"

#include "../../Library/SpriteLibrary.h"
#include "../../Unit/Sprite.h"
#include "../../Unit/Animation.h"

#include "BossArm.h"
#include "BossHand.h"

#define BOSS_MOVE_SLOW 1
#define BOSS_MOVE_NORMAL 1.5
#define BOSS_MOVE_FAST 2

class CBoss : public CEnemy
{
private:
	bool* gameOver;
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

public:
	CBoss(bool *overCon);
	void Update(DWORD dt);
	void Render();
	void SetCenter(float _x, float _y);

	void GetAllCollisionBoxes(list<LPCollisionBox> &listCo);

	void SetGoalPosition(float x, float y);
	Vector GetLocalPosition();

public:
	void HandleMovement(DWORD dt);
	bool HasReachGoal();
};

