#include "BossArm.h"

CBossArm::CBossArm(
	CBossArm* _child = NULL, 
	int sprId=ID_BOSS_RIGHT_ARM,
	float _range=0)
{
	SetType(GOTYPES::Enemy);

	child = _child;
	if (child == NULL) isTheEnd = true;

	sprite = CSpriteLibrary::GetInstance()->Get(sprId);
	sprite->GetSize(width, height);

	collisionBox = new CDynamicBox(
		this,
		-width / 2, -height / 2,
		width, height
	);
	collisionBox->SetSolid(false);

	range = _range;
}

void CBossArm::GetAllCollisionBoxes(list<LPCollisionBox>& listCo)
{
	listCo.push_back(collisionBox);

	if (child != NULL)
		child->GetAllCollisionBoxes(listCo);
}

void CBossArm::SetGoalPosition(float x, float y)
{
	if (x < -range) x = -range;
	if (x > range) x = range;

	if (y < -range) y = -range;
	if (y > range) y = range;

	localGoalPosition.x = x;
	localGoalPosition.y = y;

	if (child != NULL)
		child->SetGoalPosition(x, y);
}

Vector CBossArm::GetLocalPosition()
{
	return localPosition;
}

void CBossArm::MoveCallFromParent(DWORD dt, float vx, float vy)
{

}

void CBossArm::MoveCallFromBoss(DWORD dt, float _x, float _y)
{
	position.x += _x;
	position.y += _y;

	if (child != NULL)
		child->MoveCallFromBoss(dt, _x, _y);
}

void CBossArm::Update(DWORD dt)
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

void CBossArm::Render()
{
	if (sprite != NULL)
	{
		sprite->Draw(position.x - width / 2, position.y - height / 2);
		collisionBox->Render();
	}

	if (child != NULL)
		child->Render();
}

void CBossArm::SetPosition(float _x, float _y)
{
	position.x = _x;
	position.y = _y;

	if (child != NULL)
		child->SetPosition(_x, _y);
}

void CBossArm::Move(DWORD dt)
{
}