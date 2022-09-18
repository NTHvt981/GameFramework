#pragma once

#include "Constraints.h"
#include "Entity.h"

#include "SceneRequest.h"
#include "Sprite.h"
#include "SpriteLibrary.h"
#include "Timer.h"

#include "Explosion.h"

#include "Player.h"

class CEnemyBullet: public CEntity
{
private:
	Vector direction;
	LPSprite sprite;

	DWORD selfDestructTime;
	DWORD countUp = 0;

	bool useTimer = true;
	bool useSolid = true;

	int64_t width, height;

public:
	CEnemyBullet(Vector _direction, float _speed, float _gravity, 
		int64_t _spriteId, int64_t selfDestructTime, bool _useSolid);
	void Update(DWORD dt);
	void Render();

	static void Create(float x, float y, Vector _direction, float _speed, float _gravity,
		int64_t _spriteId, int64_t selfDestructTime, bool _useSolid);

private:
	void SelfDestruct();
};

