#pragma once

#include "../../Constraints.h"
#include "../Entity.h"

#include "../../SceneSystem/SceneRequest.h"
#include "../../Unit/Sprite.h"
#include "../../Library/SpriteLibrary.h"
#include "../../Timer/Timer.h"

class CEnemyBullet: public CEntity
{
private:
	Vector direction;
	LPSprite sprite;

	DWORD selfDestructTime;
	DWORD countUp = 0;

	bool useTimer = true;
	bool useSolid = true;

	int width, height;

public:
	CEnemyBullet(Vector _direction, float _speed, float _gravity, 
		int _spriteId, int selfDestructTime, bool _useSolid);
	void Update(DWORD dt);
	void Render();
};
