#pragma once

#include "Enemy.h"
#include "Physic.h"
#include "Constraints.h"

#include "SpriteLibrary.h"
#include "Sprite.h"
#include "Animation.h"

#include "BossArm.h"
#include "BossHand.h"

#include "Explosion.h"
#include "Utils.h"

#include "BreakableWall.h"

#include "SoundLibrary.h"

#define BOSS_MOVE_SLOW 1
#define BOSS_MOVE_NORMAL 1.5
#define BOSS_MOVE_FAST 2

#define BOSS_NORMAL 0
#define BOSS_DEFEAT 1

#define BOSS_HEALTH 65
#define BOSS_BULLET_SPEED 3
#define BOSS_SHOOT_PIVOT Vector(0, 40)

#define BOSS_MAX_RANGE 65
#define BOSS_MED_RANGE 40
#define BOSS_MIN_RANGE 20

class CBoss : public CEnemy
{
private:
	LPAnimation animation;

	int64_t width, height;

	const Vector leftHandPivot = Vector(-30, -8);
	const Vector rightHandPivot = Vector(30, -8);

	CBossHand *leftHand;
	CBossHand *rightHand;

	Vector localPosition = Vector(0, 0);
	Vector localGoalPosition = Vector(0, 0);

	std::vector<std::pair<Vector, float>> movementMatrix;
	int64_t movementIndex = 0;

	/// <summary>
	/// FOR DEBUG
	/// </summary>
	std::vector<Vector> armMovementMatrix;
	int64_t rightArmIndex = 0;
	int64_t leftArmIndex = 9;

	int64_t state = BOSS_NORMAL;
	DWORD effectCountUp = 0;
	DWORD effectWaitTime = 15;

	DWORD shootCountUp = 0;
	const DWORD shootWaitTime = 25;

	DWORD reloadCountUp = 0;
	const DWORD reloadWaitTime = 200;

	const int64_t maxMagazineSize = 5;
	int64_t magazineSize = maxMagazineSize;

public:
	CBoss();
	void Update(DWORD dt);
	void Render();
	void SetCenter(float _x, float _y);

	void GetAllCollisionBoxes(std::list<LPCollisionBox> &listCo);

	void SetGoalPosition(float x, float y);
	Vector GetLocalPosition();

	void InflictDamage(int64_t dam);
	int64_t GetHealth();
	bool IsDefeat();

public:
	void HandleMovement(DWORD dt);
	bool HasReachGoal();
	void Reset();

private:
	void NormalState(DWORD dt);
	void DefeatState(DWORD dt);

	void UpdateHand(DWORD dt, CBossHand* hand, int64_t &index);
	void HandleShoot(DWORD dt);
};

