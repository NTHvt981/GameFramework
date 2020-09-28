#pragma once
#include "..\Constraints.h"
#include "..\CollisionBox\CollisionBox.h"
#include "../Graphic/Graphic.h"

class CGameObject
{
protected:
	Vector position;
	Vector origin;
	Vector velocity;

	int speed;

	LPDIRECT3DTEXTURE9 texture;
	LPCollisionBox collisionBox = NULL;

	int state;

protected:
	void move(DWORD dt);

public:
	CGameObject(LPCWSTR texturePath);
	void SetPosition(float _x, float _y);
	Vector GetPosition();

	void SetCollisionBox(LPCollisionBox _collisionBox);
	LPCollisionBox GetCollisionBox();

	virtual void Update(DWORD dt);
	virtual void Render();

	~CGameObject();
};

