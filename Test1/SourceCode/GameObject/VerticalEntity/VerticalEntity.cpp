#include "VerticalEntity.h"

CVerticalEntity::CVerticalEntity(LPCWSTR texturePath): CGameObject(texturePath)
{
	speed = 3;
	velocity.y = speed;

	this->collisionBox = new CCollisionBox(
		this,
		0.0f, 0.0f,
		17.0f, 18.0f
	);
}

void CVerticalEntity::Update(DWORD dt)
{
	/*
	DebugOut(L"[DEBUG] Vertical collision\n left %f | right %f | top %f | bottom %f\n", 
	collisionBox->GetLeft(), collisionBox->GetRight(),
	collisionBox->GetTop(), collisionBox->GetBottom());*/

	if (position.y <= 0)
		velocity.y = speed;
	else if (position.y >= WINDOW_HEIGHT)
		velocity.y = -speed;

	move(dt);
}
