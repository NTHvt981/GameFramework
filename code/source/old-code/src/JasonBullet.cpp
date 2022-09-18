#include "JasonBullet.h"

CJasonBullet::CJasonBullet(Vector direction) : CPlayerBullet(direction)
{
	Vector size = Vector(5, 4);
	uint64_t sprId = ID_JASON_BULLET;

	speed = JASON_BULLET_SPEED;

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

	effectType = EXPLOSION_TYPES::Small;
}
