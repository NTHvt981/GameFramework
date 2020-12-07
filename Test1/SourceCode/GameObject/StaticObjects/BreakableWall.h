#pragma once

#include "..\..\Constraints.h"
#include "..\Entity.h"
#include "..\..\Collision\CollisionBox.h"
#include "..\..\Unit\Sprite.h"

#include "..\..\SceneSystem\SceneRequest.h"
#include "..\..\Library\SpriteLibrary.h"

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
};

