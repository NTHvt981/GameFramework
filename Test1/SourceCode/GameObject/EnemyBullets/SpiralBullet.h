#pragma once

#include "EnemyBullet.h"
#include "../../Debug/Utils.h"

class CSpiralBullet: public CEnemyBullet
{
private:
	float circularSpeed = 1;
	float speed = 0.25;

	Vector pivot;
	float length;

public: 
	CSpiralBullet(Vector _pivot, int _spriteId, int selfDestructTime);
	void Update(DWORD dt);
	void SetLength(float _length);

	static void Create(float x, float y, 
		Vector _pivot, int _spriteId, int selfDestructTime);

protected:
	void Move(DWORD dt);
};

