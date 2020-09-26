#include "HorizontalEntity.h"

CHorizontalEntity::CHorizontalEntity(LPCWSTR texturePath):CGameObject(texturePath)
{
	speed = 5;
	velocity.x = 0;

	this->collisionBox = new CCollisionBox(
		this,
		0.0f, 0.0f,
		17.0f, 18.0f
	);
}

void CHorizontalEntity::Update(DWORD dt)
{
	//if (position.x <= 0)
	//	velocity.x = speed;
	//else if (position.x >= WINDOW_WIDTH)
	//	velocity.x = -speed;

	move(dt);
}
