#pragma once

#include "EnemyBullet.h"
#include "Utils.h"

class CSpiralBullet: public CEnemyBullet
{
private:
	float circularSpeed = 1;
	float speed = 0.25;

	Vector pivot;
	float length;

public: 
	CSpiralBullet(Vector _pivot, int64_t _spriteId, int64_t selfDestructTime);
	void Update(DWORD dt);
	void SetLength(float _length);

	static void Create(float x, float y, 
		Vector _pivot, int64_t _spriteId, int64_t selfDestructTime);

protected:
	void Move(DWORD dt);
};

