#include "HorizontalEntity.h"

CHorizontalEntity::CHorizontalEntity(LPCWSTR texturePath):CGameObject(texturePath)
{
	speed = 5;
	velocity.x = speed;
}

void CHorizontalEntity::Update(DWORD dt)
{
	if (position.x <= 0)
		velocity.x = speed;
	else if (position.x >= WINDOW_WIDTH)
		velocity.x = -speed;

	move(dt);
}
