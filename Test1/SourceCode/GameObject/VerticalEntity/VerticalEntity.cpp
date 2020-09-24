#include "VerticalEntity.h"

CVerticalEntity::CVerticalEntity(LPCWSTR texturePath): CGameObject(texturePath)
{
	speed = 3;
	velocity.y = speed;
}

void CVerticalEntity::Update(DWORD dt)
{
	if (position.y <= 0)
		velocity.y = speed;
	else if (position.y >= WINDOW_HEIGHT)
		velocity.y = -speed;

	move(dt);
}
