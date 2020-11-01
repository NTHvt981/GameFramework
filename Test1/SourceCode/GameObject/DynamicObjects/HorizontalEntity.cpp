#include "HorizontalEntity.h"

CHorizontalEntity::CHorizontalEntity():CEntity()
{
	speed = 5;
	state = MOVE_RIGHT_STATE;

	this->collisionBox = new CDynamicBox(
		this,
		0.0f, 0.0f,
		17.0f, 18.0f
	);
}

void CHorizontalEntity::Update(DWORD dt)
{
	switch (state)
	{
	case MOVE_RIGHT_STATE:
		MoveRight();
		break;
	case MOVE_LEFT_STATE:
		MoveLeft();
		break;

	default:
		break;
	}

	move(dt);
}

void CHorizontalEntity::MoveLeft()
{
	if (position.x >= CAMERA_WIDTH)
		state = MOVE_RIGHT_STATE;

	velocity.x = speed;
}

void CHorizontalEntity::MoveRight()
{
	if (position.x <= 0)
		state = MOVE_LEFT_STATE;

	velocity.x = -speed;
}
