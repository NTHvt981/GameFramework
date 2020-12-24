#include "Boss.h"

CBoss::CBoss(bool* overCon)
{
	SetType(GOTYPES::Enemy);
	gameOver = overCon;

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
	armMovementMatrix.push_back(Vector(100, 0));
	armMovementMatrix.push_back(Vector(0, 100));
	armMovementMatrix.push_back(Vector(-50, 100));
	armMovementMatrix.push_back(Vector(-100, 0));
	armMovementMatrix.push_back(Vector(0, 0));
	armMovementMatrix.push_back(Vector(0, -100));
	armMovementMatrix.push_back(Vector(0, 0));

	rightHand->SetGoalPosition(
		armMovementMatrix[rightArmIndex].x, armMovementMatrix[rightArmIndex].y
	);

	movementMatrix.push_back(pair<Vector, float>(Vector(0, 0), BOSS_MOVE_NORMAL));
	movementMatrix.push_back(pair<Vector, float>(Vector(range, 0), BOSS_MOVE_NORMAL));
	movementMatrix.push_back(pair<Vector, float>(Vector(0, range), BOSS_MOVE_NORMAL));
	movementMatrix.push_back(pair<Vector, float>(Vector(-range, 0), BOSS_MOVE_NORMAL));
	movementMatrix.push_back(pair<Vector, float>(Vector(0, -range), BOSS_MOVE_NORMAL));
	movementMatrix.push_back(pair<Vector, float>(Vector(range, -range), BOSS_MOVE_NORMAL));
	movementMatrix.push_back(pair<Vector, float>(Vector(range, range), BOSS_MOVE_FAST));
	movementMatrix.push_back(pair<Vector, float>(Vector(-range, range), BOSS_MOVE_FAST));
	movementMatrix.push_back(pair<Vector, float>(Vector(-range, -range), BOSS_MOVE_FAST));
	movementMatrix.push_back(pair<Vector, float>(Vector(0, 0), BOSS_MOVE_NORMAL));
}

void CBoss::Update(DWORD dt)
{
	rightHand->Update(dt);

	if (rightHand->HasReachGoal())
	{
		rightArmIndex++;

		if (rightArmIndex > armMovementMatrix.size() - 1)
			rightArmIndex = 0;

		rightHand->SetGoalPosition(
			armMovementMatrix[rightArmIndex].x, armMovementMatrix[rightArmIndex].y
		);
	}


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
	if (x < -range) x = -range;
	if (x > range) x = range;

	if (y < -range) y = -range;
	if (y > range) y = range;

	localGoalPosition.x = x;
	localGoalPosition.y = y;
}

Vector CBoss::GetLocalPosition()
{
	return localPosition;
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
