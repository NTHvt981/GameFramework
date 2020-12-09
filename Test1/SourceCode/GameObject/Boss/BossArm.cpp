#include "BossArm.h"

CBossArm::CBossArm(
	bool *_isStretchAll, 
	CBossArm* _child = NULL, 
	bool isTheHead=false, 
	int sprId=ID_BOSS_RIGHT_ARM)
{
	isStretchAll = _isStretchAll;

	SetType(GOTYPES::Enemy);

	child = _child;
	if (child == NULL) isTheEnd = true;

	if (!isTheHead)
	{
		sprite = CSpriteLibrary::GetInstance()->Get(sprId);
		sprite->GetSize(width, height);

		collisionBox = new CDynamicBox(
			this,
			-width / 2, -height / 2,
			width, height
		);
		collisionBox->SetSolid(false);
	}
}

void CBossArm::MoveCallFromParent(DWORD dt, float vx, float vy)
{
	if (isTheEnd)
	{
		*isStretchAll = true;
		return;
	}
	else if (*isStretchAll)
	{
		return;
	}

	Vector newPos;
	newPos.Set(position.x + vx, position.y + vy);

	Vector newDistance;
	newDistance.Set(
		abs(newPos.x - child->GetPosition().x),
		abs(newPos.y - child->GetPosition().y)
	);

	Vector velocityPassOn;
	float _vx = 0, _vy = 0;

	if (newDistance.x > maxDistance)
	{
		if (vx > 0)
		{
			_vx = newDistance.x - maxDistance;
			//vx = vx - (newDistance.x - maxDistance);
		}
		else
		{
			_vx = -newDistance.x + maxDistance;
			//vx = vx + (newDistance.x - maxDistance);
		}
	}

	if (newDistance.y > maxDistance)
	{
		if (vy > 0)
		{
			_vy = newDistance.y - maxDistance;
			//vy = vy - (newDistance.y - maxDistance);
		}
		else
		{
			_vy = -newDistance.y + maxDistance;
			//vy = vy + (newDistance.y - maxDistance);
		}
	}

	if (_vx != 0 || _vy != 0)
		child->MoveCallFromParent(dt, _vx, _vy);

	position.x += vx;
	position.y += vy;
	if (sprite != NULL)
		collisionBox->Update();
}

void CBossArm::MoveCallFromBoss(DWORD dt, float _x, float _y)
{
	position.x += _x;
	position.y += _y;

	if (!isTheEnd)
		child->MoveCallFromBoss(dt, _x, _y);
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

void CBossArm::SetIsStretchAllAddress(bool* _isStretchAll)
{
	isStretchAll = _isStretchAll;
}

void CBossArm::Move(DWORD dt)
{
}