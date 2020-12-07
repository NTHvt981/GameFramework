#pragma once

#include "../GameObject/Enemies/Enemy.h"
#include "../GameObject/StaticObjects/BreakableWall.h"
#include "../Timer/Timer.h"
#include "../Constraints.h"
#include "../Unit/Sprite.h"
#include "../Library/SpriteLibrary.h"

#include "../SceneSystem/SceneRequest.h"

class CPlayerBullet: public CEntity
{
protected:
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

