#pragma once

#include "GameObject.h"
#include "..\Constraints.h"
#include "..\Graphic\Graphic.h"
#include "..\Library\TextureLibrary.h"
#include "..\Collision\CollisionBox.h"

class CEntity: public CGameObject {
protected:
	GOTYPES type = GOTYPES::Entity;

	Vector position;
	Vector origin;
	Vector velocity;

	int speed;

	LPDIRECT3DTEXTURE9 texture;
	LPCollisionBox collisionBox = NULL;
	list<LPEntity> collidedEntities;

protected:
	void move(DWORD dt);

public:
	CEntity(LPCWSTR texturePath);
	void SetPosition(float _x, float _y);
	Vector GetPosition();

	void SetCollisionBox(LPCollisionBox _collisionBox);
	LPCollisionBox GetCollisionBox();

	bool IsCollidedWith(GOTYPES type);
	void GetCollidedWith(GOTYPES type, list<LPEntity> &collidedObjs);

	void Update(DWORD dt);
	void Render();

	~CEntity();
};

