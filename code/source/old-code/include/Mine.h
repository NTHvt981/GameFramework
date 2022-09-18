#pragma once

#include "Enemy.h"
#include "Animation.h"

class CMine: public CEnemy
{
public:
	CMine();
	void Update(DWORD dt);
	void Render();

private:
	void Explode();
};

