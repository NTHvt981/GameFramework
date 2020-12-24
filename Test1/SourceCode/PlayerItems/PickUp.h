#pragma once

#include "../Timer/Timer.h"
#include "../Constraints.h"
#include "../Unit/Sprite.h"
#include "../Library/SpriteLibrary.h"

#include "../SceneSystem/SceneRequest.h"
#include "../GameObject/Entity.h"
#include "../Player/Player.h"

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

