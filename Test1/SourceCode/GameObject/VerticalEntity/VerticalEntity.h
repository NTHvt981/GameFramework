#pragma once
#include "..\GameObject.h"

class CVerticalEntity: public CGameObject
{
public:
	CVerticalEntity(LPCWSTR texturePath);
	void Update(DWORD dt);
};

