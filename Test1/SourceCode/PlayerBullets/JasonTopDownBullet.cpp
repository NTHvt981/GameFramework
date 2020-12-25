#include "JasonTopDownBullet.h"

CJasonTopDownBullet::CJasonTopDownBullet(Vector direction): CPlayerBullet(direction)
{
	unsigned int sprId;
	speed = JASON_TOPDOWN_BULLET_SPEED;

	if (direction.x == 1)
	{
		sprId = ID_JASON_TOPDOWN_BULLET_RIGHT;
		velocity = Vector(speed, 0);
	}
	else if (direction.x == -1)
	{
		sprId = ID_JASON_TOPDOWN_BULLET_LEFT;
		velocity = Vector(-speed, 0);
	}

	else if (direction.y == -1)
	{
		sprId = ID_JASON_TOPDOWN_BULLET_UP;
		velocity = Vector(0, -speed);
	}
	else if (direction.y == 1)
	{
		sprId = ID_JASON_TOPDOWN_BULLET_DOWN;
		velocity = Vector(0, speed);
	}

	sprite = CSpriteLibrary::GetInstance()->Get(sprId);

	sprite->GetSize(width, height);

	collisionBox = new CDynamicBox(
		this, -width/2, -height/2, width, height
	);
	collisionBox->SetSolid(false);
}

void CJasonTopDownBullet::Render()
{
	sprite->Draw(position.x - width / 2, position.y - height / 2);
	collisionBox->Render();
}
