#pragma once
#include "..\GameObject.h"

class CVerticalEntity: public CGameObject
{
public:
	CVerticalEntity(LPCWSTR texturePath);
	void Update(DWORD dt);

	//state functions (get called depending on states)
private:
	void MoveUp();
	void MoveDown();
};

