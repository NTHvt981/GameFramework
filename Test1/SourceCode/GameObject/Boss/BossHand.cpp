#include "BossHand.h"

void CBossHand::setUpBossArm(int parentId)
{
	int id;
	if (parentId == ID_BOSS_LEFT_HAND)
		id = ID_BOSS_LEFT_ARM;
	else
		id = ID_BOSS_RIGHT_ARM;

	CBossArm* arm1 = new CBossArm(&isStretchAll, NULL, false, id);
	CBossArm* arm2 = new CBossArm(&isStretchAll, arm1, false, id);
	CBossArm* arm3 = new CBossArm(&isStretchAll, arm2, false, id);
	CBossArm* arm4 = new CBossArm(&isStretchAll, arm3, false, id);
	CBossArm* arm5 = new CBossArm(&isStretchAll, arm4, true, id);

	child = arm5;
}

CBossHand::CBossHand(int id) : CEntity()
{
	sprite = CSpriteLibrary::GetInstance()->Get(id);
	sprite->GetSize(width, height);

	collisionBox = new CDynamicBox(
		this,
		-width / 2, -height / 4,
		width, height
	);
	collisionBox->SetSolid(false);

	setUpBossArm(id);
}

void CBossHand::SetGoalPosition(float x, float y)
{
	isStretchAll = false;

	localGoalPosition.x = x;
	localGoalPosition.y = y;
}

Vector CBossHand::GetLocalPosition()
{
	return localPosition;
}

void CBossHand::MoveCallFromBoss(DWORD dt, float _x, float _y)
{
	position.x += _x;
	position.y += _y;

	child->MoveCallFromBoss(dt, _x, _y);
}

void CBossHand::Update(DWORD dt)
{
	float _x = localGoalPosition.x - localPosition.x;
	float _y = localGoalPosition.y - localPosition.y;

	int _signX = _x >= 0 ? 1 : -1;
	int _signY = _y >= 0 ? 1 : -1;
	
	if (_x != 0 || _y != 0)
	{
		if (isStretchAll)
		{
			localGoalPosition.x = localPosition.x;
			localGoalPosition.y = localPosition.y;

			return;
		}

		velocity.x = _signX * speed;
		velocity.y = _signY * speed;

		if (abs(velocity.x) > abs(_x)) velocity.x = _signX * _x;
		if (abs(velocity.y) > abs(_y)) velocity.y = _signY * _y;

		localPosition.x += velocity.x;
		localPosition.y += velocity.y;

		position.x += velocity.x;
		position.y += velocity.y;
		collisionBox->Update();

		child->MoveCallFromParent(dt, velocity.x, velocity.y);
	}
}

void CBossHand::Render()
{
	sprite->Draw(position.x - width / 2, position.y - height / 4);
	collisionBox->Render();

	child->Render();
}

void CBossHand::SetPosition(float _x, float _y)
{
	position.x = _x;
	position.y = _y;

	child->SetPosition(_x, _y);
}

void CBossHand::MoveAxis(float &cur, float &goal)
{
}

bool CBossHand::HasReachGoal()
{
	if (localGoalPosition.x == localPosition.x &&
		localGoalPosition.y == localPosition.y)
	{
		int a = 1;
	}

	return (localGoalPosition.x == localPosition.x && 
		localGoalPosition.y == localPosition.y);
}
