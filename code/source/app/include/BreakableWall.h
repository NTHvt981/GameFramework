#pragma once

#include "Constraints.h"
#include "Entity.h"
#include "CollisionBox.h"
#include "Sprite.h"

#include "SceneRequest.h"
#include "SpriteLibrary.h"

#include "Explosion.h"

class CBreakableWall: public CEntity
{
private:
	float left;
	float top;
	LPSprite sprite;

protected:
	void Move(DWORD dt);
public:
	void SetPosition(float _x, float _y);
	CBreakableWall(float l, float t, float r, float b);
	void Update(DWORD dt);
	void Render();

	void Destroy();

public:
	static bool Switch;
};

