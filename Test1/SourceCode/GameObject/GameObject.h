#pragma once
#include "..\Constraints.h"

class CGameObject
{
protected:
	Vector position;
	Vector origin;
	Vector velocity;

	int speed;

	LPDIRECT3DTEXTURE9 texture;

protected:
	void move(DWORD dt);

public:
	CGameObject(LPCWSTR texturePath);
	void SetPosition(float _x, float _y);

	virtual void Update(DWORD dt);
	virtual void Render();

	~CGameObject();
};

typedef CGameObject* LPGameObject;
