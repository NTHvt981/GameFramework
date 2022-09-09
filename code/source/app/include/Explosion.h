#pragma once

#include "Entity.h"
#include "CollisionBox.h"

#include "Animation.h"
#include "SpriteLibrary.h"

#include "SceneRequest.h"

#include "SoundLibrary.h"

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

