#pragma once

#include "..\Entity.h"
#include "..\..\Collision\CollisionBox.h"

#include "..\..\Unit\Animation.h"
#include "..\..\Library\SpriteLibrary.h"

#include "..\..\SceneSystem\SceneRequest.h"

#include "../../GraphicAndSound/SoundLibrary.h"

enum EXPLOSION_TYPES
{
	Small,
	Medium,
	Big
};

class CExplosion : public CEntity
{
private:
	LPAnimation animation;

protected:
	void Move(DWORD dt);
public:
	CExplosion(EXPLOSION_TYPES type);
	void Update(DWORD dt);
	void Render();

	static void CreateExplosion(float x, float y, EXPLOSION_TYPES type);
};

