#include "BossHand.h"

void CBossHand::setUpBossArm(int parentId)
{
	int id;
	if (parentId == ID_BOSS_LEFT_HAND)
		id = ID_BOSS_LEFT_ARM;
	else
		id = ID_BOSS_RIGHT_ARM;

	CBossArm* arm1 = new CBossArm(NULL, id, 0);
	CBossArm* arm2 = new CBossArm(arm1, id, 20);
	CBossArm* arm3 = new CBossArm(arm2, id, 40);
	CBossArm* arm4 = new CBossArm(arm3, id, 60);

	child = arm4;
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

void CBossHand::GetAllCollisionBoxes(list<LPCollisionBox>& listCo)
{
	listCo.push_back(collisionBox);

	child->GetAllCollisionBoxes(listCo);
}

void CBossHand::SetGoalPosition(float x, float y)
{
	if (x < -range) x = -range;
	if (x > range) x = range;

	if (y < -range) y = -range;
	if (y > range) y = range;

	localGoalPosition.x = x;
	localGoalPosition.y = y;

	child->SetGoalPosition(x, y);
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

	collisionBox->Update();

	if (child != NULL) child->Update(dt);
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
	//if (localGoalPosition.x == localPosition.x &&
	//	localGoalPosition.y == localPosition.y)
	//{
	//	int a = 1;
	//}

	return (localGoalPosition.x == localPosition.x && 
		localGoalPosition.y == localPosition.y);
}
