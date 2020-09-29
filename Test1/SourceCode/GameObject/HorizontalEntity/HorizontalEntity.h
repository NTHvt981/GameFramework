#pragma once
#include "..\GameObject.h"


class CHorizontalEntity: public CGameObject
{
public:
	CHorizontalEntity(LPCWSTR texturePath);
	void Update(DWORD dt);

	//state functions (get called depending on states)
private:
	void MoveLeft();
	void MoveRight();
};


