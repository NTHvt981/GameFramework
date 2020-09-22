#pragma once
#include "..\Constraints.h"

class CGameObject
{
protected:
	float x;
	float y;
	float vx = 0;
	float vy = 0;

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

