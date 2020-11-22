#pragma once

#include "../GameObject/Entity.h"
#include "../Timer/Timer.h"
#include "../Constraints.h"
#include "../Unit/Sprite.h"
#include "../Library/SpriteLibrary.h"

#include "../Game/Game.h"
#include "../Game/GameRequest.h"

class CPlayerBullet: public CEntity
{
private:
	float speed = 5;
	const int damage = 2;
	Vector old_velocity;
	LPSprite sprite;
	CTimer* selfDestructTimer;

public:
	CPlayerBullet(Vector direction);
	
	void Update(DWORD dt);
	void Render();
};

