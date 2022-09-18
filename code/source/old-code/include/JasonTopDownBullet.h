#pragma once

#include "PlayerBullet.h"

class CJasonTopDownBullet : public CPlayerBullet
{
public:
	CJasonTopDownBullet(Vector direction);

public:
	void Render();
};

