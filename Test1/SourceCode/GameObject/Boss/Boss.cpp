#include "Boss.h"

CBoss::CBoss()
{
	SetType(GOTYPES::Enemy);
	SetMaxHealth(BOSS_HEALTH);

	animation = new CAnimation(500);
	animation->Add(ID_BOSS_HEAD_1);
	animation->Add(ID_BOSS_HEAD_2);
	animation->Add(ID_BOSS_HEAD_3);
	animation->Add(ID_BOSS_HEAD_4);
	animation->Add(ID_BOSS_HEAD_5);
	animation->Add(ID_BOSS_HEAD_6);
	animation->Add(ID_BOSS_HEAD_7);
	animation->Add(ID_BOSS_HEAD_8);

	animation->GetSize(width, height);
	collisionBox = new CDynamicBox(
		this,
		-width / 2, -height / 2,
		width, height
	);

	leftHand = new CBossHand(
		ID_BOSS_LEFT_HAND);
	rightHand = new CBossHand(
		ID_BOSS_RIGHT_HAND);

	armMovementMatrix.push_back(Vector(100, 0));
	armMovementMatrix.push_back(Vector(100, 100));
	armMovementMatrix.push_back(Vector(0, 100));
	armMovementMatrix.push_back(Vector(0, 0));

	armMovementMatrix.push_back(Vector(0, -50));
	armMovementMatrix.push_back(Vector(0, 100));
	armMovementMatrix.push_back(Vector(50, 100));
	armMovementMatrix.push_back(Vector(-50, 100));
	armMovementMatrix.push_back(Vector(0, 0));

	armMovementMatrix.push_back(Vector(-100, 0));
	armMovementMatrix.push_back(Vector(-100, 100));
	armMovementMatrix.push_back(Vector(0, 100));
	armMovementMatrix.push_back(Vector(0, 0));

	armMovementMatrix.push_back(Vector(0, -50));
	armMovementMatrix.push_back(Vector(0, 100));
	armMovementMatrix.push_back(Vector(50, 100));
	armMovementMatrix.push_back(Vector(-50, 100));
	armMovementMatrix.push_back(Vector(0, 0));

	rightHand->SetGoalPosition(
		armMovementMatrix[rightArmIndex].x, armMovementMatrix[rightArmIndex].y
	);
	leftHand->SetGoalPosition(
		armMovementMatrix[leftArmIndex].x, armMovementMatrix[leftArmIndex].y
	);

	movementMatrix.push_back(pair<Vector, float>(Vector(BOSS_MAX_RANGE, 0), BOSS_MOVE_NORMAL));
	movementMatrix.push_back(pair<Vector, float>(Vector(BOSS_MED_RANGE, BOSS_MIN_RANGE), BOSS_MOVE_SLOW));
	movementMatrix.push_back(pair<Vector, float>(Vector(0, 0), BOSS_MOVE_SLOW));

	movementMatrix.push_back(pair<Vector, float>(Vector(-BOSS_MAX_RANGE, 0), BOSS_MOVE_NORMAL));
	movementMatrix.push_back(pair<Vector, float>(Vector(-BOSS_MED_RANGE, BOSS_MIN_RANGE), BOSS_MOVE_SLOW));
	movementMatrix.push_back(pair<Vector, float>(Vector(0, 0), BOSS_MOVE_SLOW));

	movementMatrix.push_back(pair<Vector, float>(Vector(0, -BOSS_MAX_RANGE), BOSS_MOVE_SLOW));
	movementMatrix.push_back(pair<Vector, float>(Vector(0, -BOSS_MED_RANGE), BOSS_MOVE_NORMAL));
	movementMatrix.push_back(pair<Vector, float>(Vector(0, BOSS_MAX_RANGE), BOSS_MOVE_FAST));
	movementMatrix.push_back(pair<Vector, float>(Vector(BOSS_MED_RANGE, BOSS_MAX_RANGE), BOSS_MOVE_SLOW));
	movementMatrix.push_back(pair<Vector, float>(Vector(0, 0), BOSS_MOVE_SLOW));

	movementMatrix.push_back(pair<Vector, float>(Vector(BOSS_MAX_RANGE, 0), BOSS_MOVE_NORMAL));
	movementMatrix.push_back(pair<Vector, float>(Vector(BOSS_MED_RANGE, BOSS_MIN_RANGE), BOSS_MOVE_SLOW));
	movementMatrix.push_back(pair<Vector, float>(Vector(0, 0), BOSS_MOVE_SLOW));

	movementMatrix.push_back(pair<Vector, float>(Vector(-BOSS_MAX_RANGE, 0), BOSS_MOVE_NORMAL));
	movementMatrix.push_back(pair<Vector, float>(Vector(-BOSS_MED_RANGE, BOSS_MIN_RANGE), BOSS_MOVE_SLOW));
	movementMatrix.push_back(pair<Vector, float>(Vector(0, 0), BOSS_MOVE_SLOW));

	movementMatrix.push_back(pair<Vector, float>(Vector(0, -BOSS_MAX_RANGE), BOSS_MOVE_SLOW));
	movementMatrix.push_back(pair<Vector, float>(Vector(0, -BOSS_MED_RANGE), BOSS_MOVE_NORMAL));
	movementMatrix.push_back(pair<Vector, float>(Vector(0, BOSS_MAX_RANGE), BOSS_MOVE_FAST));
	movementMatrix.push_back(pair<Vector, float>(Vector(-BOSS_MED_RANGE, BOSS_MAX_RANGE), BOSS_MOVE_SLOW));
	movementMatrix.push_back(pair<Vector, float>(Vector(0, 0), BOSS_MOVE_SLOW));
}

void CBoss::Update(DWORD dt)
{
	switch (state)
	{
	case BOSS_NORMAL:
		NormalState(dt);
		break;
	case BOSS_DEFEAT:
		DefeatState(dt);
		break;
	default:
		break;
	}
}

void CBoss::Render()
{
	animation->Render(
		position.x - width / 2,
		position.y - height / 2
	);
	collisionBox->Render();

	leftHand->Render();
	rightHand->Render();
}

void CBoss::SetCenter(float _x, float _y)
{
	SetPosition(_x, _y);

	leftHand->SetPosition(
		position.x + leftHandPivot.x,
		position.y + leftHandPivot.y);
	rightHand->SetPosition(
		position.x + rightHandPivot.x,
		position.y + rightHandPivot.y);
}

void CBoss::GetAllCollisionBoxes(list<LPCollisionBox>& listCo)
{
	listCo.clear();

	listCo.push_back(collisionBox);

	leftHand->GetAllCollisionBoxes(listCo);
	rightHand->GetAllCollisionBoxes(listCo);
}

void CBoss::SetGoalPosition(float x, float y)
{
	if (x < -BOSS_MAX_RANGE) x = -BOSS_MAX_RANGE;
	if (x > BOSS_MAX_RANGE) x = BOSS_MAX_RANGE;

	if (y < -BOSS_MAX_RANGE) y = -BOSS_MAX_RANGE;
	if (y > BOSS_MAX_RANGE) y = BOSS_MAX_RANGE;

	localGoalPosition.x = x;
	localGoalPosition.y = y;
}

Vector CBoss::GetLocalPosition()
{
	return localPosition;
}

void CBoss::InflictDamage(int dam)
{
	health = max(0, health - dam);

	if (health == 0)
	{
		CBreakableWall::Switch = true;
		state = BOSS_DEFEAT;
	}
}

int CBoss::GetHealth()
{
	return health;
}

bool CBoss::IsDefeat()
{
	return state == BOSS_DEFEAT;
}

void CBoss::HandleMovement(DWORD dt)
{
	float _x = localGoalPosition.x - localPosition.x;
	float _y = localGoalPosition.y - localPosition.y;

	int _signX = _x >= 0 ? 1 : -1;
	int _signY = _y >= 0 ? 1 : -1;

	Vector localNewPosition;

	if (_signX > 0)
	{
		localNewPosition.x = min(localPosition.x + speed, localGoalPosition.x);
	}
	else
	{
		localNewPosition.x = max(localPosition.x - speed, localGoalPosition.x);
	}

	if (_signY > 0)
	{
		localNewPosition.y = min(localPosition.y + speed, localGoalPosition.y);
	}
	else
	{
		localNewPosition.y = max(localPosition.y - speed, localGoalPosition.y);
	}

	Vector remainVel;
	remainVel.Set(
		localNewPosition.x - localPosition.x,
		localNewPosition.y - localPosition.y
	);

	localPosition.Set(localNewPosition.x, localNewPosition.y);
	position.Set(position.x + remainVel.x, position.y + remainVel.y);

	leftHand->MoveCallFromBoss(dt, remainVel.x, remainVel.y);
	rightHand->MoveCallFromBoss(dt, remainVel.x, remainVel.y);

	collisionBox->Update();
}

bool CBoss::HasReachGoal()
{
	return (localGoalPosition.x == localPosition.x &&
		localGoalPosition.y == localPosition.y);
}

void CBoss::Reset()
{
	state = BOSS_NORMAL;
	health = maxHealth;
}

void CBoss::NormalState(DWORD dt)
{
	animation->SetMode(ANIMATION_NORMAL);

	UpdateHand(dt, leftHand, leftArmIndex);
	UpdateHand(dt, rightHand, rightArmIndex);
	HandleShoot(dt);

	if (!HasReachGoal())
		HandleMovement(dt);
	else
	{
		movementIndex++;

		if (movementIndex > movementMatrix.size() - 1)
			movementIndex = 0;

		SetGoalPosition(
			movementMatrix[movementIndex].first.x, movementMatrix[movementIndex].first.y
		);
		speed = movementMatrix[movementIndex].second;
	}
}

void CBoss::DefeatState(DWORD dt)
{
	animation->SetMode(ANIMATION_PAUSE);

	effectCountUp += dt;
	if (effectCountUp >= effectWaitTime)
	{
		effectCountUp = 0;

		float min_x, max_x, min_y, max_y;
		min_x = position.x - width / 2;
		max_x = position.x + width / 2;
		min_y = position.y - height / 2;
		max_y = position.y + height / 2;

		float spawn_x, spawn_y;
		spawn_x = CUtils::randRange(min_x, max_x);
		spawn_y = CUtils::randRange(min_y, max_y);

		if (CUtils::lottery(0.3))
			CExplosion::CreateExplosion(spawn_x, spawn_y, EXPLOSION_TYPES::Big);
		else if (CUtils::lottery(0.7))
			CExplosion::CreateExplosion(spawn_x, spawn_y, EXPLOSION_TYPES::Medium);
		else
			CExplosion::CreateExplosion(spawn_x, spawn_y, EXPLOSION_TYPES::Small);
	}
}

void CBoss::UpdateHand(DWORD dt, CBossHand* hand, int& index)
{
	hand->Update(dt);
	if (hand->HasReachGoal())
	{
		index++;

		if (index > armMovementMatrix.size() - 1)
			index = 0;

		hand->SetGoalPosition(
			armMovementMatrix[index].x, armMovementMatrix[index].y
		);
	}
}

void CBoss::HandleShoot(DWORD dt)
{
	if (magazineSize == 0)
	{
		reloadCountUp += dt;
		if (reloadCountUp >= reloadWaitTime)
		{
			reloadCountUp = 0;
			magazineSize = maxMagazineSize;
		}
	}
	else
	{
		shootCountUp += dt;
		if (shootCountUp >= shootWaitTime)
		{
			shootCountUp = 0;
			magazineSize = max(magazineSize - 1, 0);

			Vector center = GetCenter();
			Vector pCenter = CPlayer::GetCurrentPlayer()->GetCenter();
			Vector dir = Vector(pCenter.x - center.x, pCenter.y - center.y);
			CEnemyBullet::Create(
				center.x + BOSS_SHOOT_PIVOT.x, 
				center.y + BOSS_SHOOT_PIVOT.y,
				dir, BOSS_BULLET_SPEED, 0, ID_ENEMY_TOPDOWN_BULLET_1, 300, true
			);
		}
	}
}
