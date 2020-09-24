#pragma once
#include "..\GameObject.h"


class CHorizontalEntity: public CGameObject
{
public:
	CHorizontalEntity(LPCWSTR texturePath);
	void Update(DWORD dt);
};


