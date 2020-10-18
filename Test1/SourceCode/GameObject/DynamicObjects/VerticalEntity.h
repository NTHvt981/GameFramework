#pragma once

#include "../Entity.h"
#include "..\..\Constraints.h"

class CVerticalEntity: public CEntity
{
public:
	CVerticalEntity(LPCWSTR texturePath);
	void Update(DWORD dt);

	//state functions (get called depending on states)
private:
	void MoveUp();
	void MoveDown();
};
