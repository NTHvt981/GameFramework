#include "VerticalEntity.h"

CVerticalEntity::CVerticalEntity(LPCWSTR texturePath): CEntity(texturePath)
{
	speed = 3;
	state = MOVE_DOWN_STATE;

	this->collisionBox = new CDynamicBox(
		this,
		0.0f, 0.0f,
		17.0f, 18.0f
	);
}

void CVerticalEntity::Update(DWORD dt)
{
	switch (state)
	{
	case MOVE_DOWN_STATE:
		MoveDown();
		break;
	case MOVE_UP_STATE:
		MoveUp();
		break;

	default:
		break;
	}


	move(dt);
}

void CVerticalEntity::MoveUp()
{
	if (position.y >= WINDOW_HEIGHT)
		state = MOVE_DOWN_STATE;

	velocity.y = speed;
}

void CVerticalEntity::MoveDown()
{
	if (position.y <= 0)
		state = MOVE_UP_STATE;

	velocity.y = -speed;
}
