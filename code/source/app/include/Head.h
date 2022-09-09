#pragma once

#include "Enemy.h"
#include "Animation.h"

#define HEAD_MOVE_SPEED 0.3

class CHead : public CEnemy
{
private:
	LPAnimation animation;
	const float speed = HEAD_MOVE_SPEED;
	
public:
	CHead();
	void Update(DWORD dt);
	void Render();
};

