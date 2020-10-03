#pragma once

#include "GameObject.h"
#include "..\Constraints.h"
#include "..\Graphic\Graphic.h"
#include "..\Library\TextureLibrary.h"
#include "..\Collision\DynamicBox.h"

class CEntity: public CGameObject {
protected:
	Vector position;
	Vector origin;
	Vector velocity;

	int speed;

	LPDIRECT3DTEXTURE9 texture;
	LPDynamicBox collisionBox = NULL;
	list<LPGameObject> collidedEntities;

protected:
	void move(DWORD dt);

public:
	CEntity(LPCWSTR texturePath);
	void SetPosition(float _x, float _y);
	Vector GetPosition();

	LPDynamicBox GetCollisionBox();

	bool IsCollidedWith(GOTYPES type);
	void GetCollidedWith(GOTYPES type, list<LPGameObject> &collidedObjs);

	void Update(DWORD dt);
	void Render();

	~CEntity();
};

