#include "SophiaBullet.h"

CSophiaBullet::CSophiaBullet(Vector direction): CPlayerBullet(direction)
{
	Vector size = Vector(20, 6);
	unsigned int sprId;

	if (direction.x == 1)
	{
		sprId = ID_SOPHIA_BULLET_RIGHT;
		velocity = Vector(speed, 0);
	}
	else if (direction.x == -1)
	{
		sprId = ID_SOPHIA_BULLET_LEFT;
		velocity = Vector(-speed, 0);
	}
	else
	{
		if (direction.y == -1)
		{
			sprId = ID_SOPHIA_BULLET_UP;
			velocity = Vector(0, -speed);

			//swap size w and h of coli box
			int temp = size.x;
			size.x = size.y;
			size.y = temp;
		}
	}

	collisionBox = new CDynamicBox(
		this, 0, 0, size.x, size.y
	);
	collisionBox->SetSolid(false);

	sprite = CSpriteLibrary::GetInstance()->Get(sprId);
}
