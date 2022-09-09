#pragma once

#include "Timer.h"
#include "Constraints.h"
#include "Sprite.h"
#include "SpriteLibrary.h"

#include "SceneRequest.h"
#include "Entity.h"
#include "Player.h"

class CPickUp : public CEntity
{
protected:
	LPSprite sprite;
	float width = 16, height = 16;
	void virtual InContactWithPlayer();

public:
	CPickUp();

	void Update(DWORD dt);
	void Render();
};

