#include "JasonBullet.h"

CJasonBullet::CJasonBullet(Vector direction) : CPlayerBullet(direction)
{
	Vector size = Vector(5, 4);
	unsigned int sprId = ID_JASON_BULLET;

	speed = 4;

	if (direction.x == 1)
	{
		velocity = Vector(speed, 0);
	}
	else if (direction.x == -1)
	{
		velocity = Vector(-speed, 0);
	}

	collisionBox = new CDynamicBox(
		this, 0, 0, size.x, size.y
	);
	collisionBox->SetSolid(false);

	sprite = CSpriteLibrary::GetInstance()->Get(sprId);
}
