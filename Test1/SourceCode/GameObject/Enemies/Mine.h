#pragma once

#include "../Enemies/Enemy.h"
#include "../../Unit/Animation.h"

class CMine: public CEnemy
{
public:
	CMine();
	void Update(DWORD dt);
	void Render();

private:
	void Explode();
};

