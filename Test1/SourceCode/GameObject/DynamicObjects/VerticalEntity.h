#pragma once

#include "..\..\Constraints.h"
#include "DynamicEntity.h"

class CVerticalEntity: public CDynamicEntity
{
public:
	CVerticalEntity(LPCWSTR texturePath);
	void Update(DWORD dt);

	//state functions (get called depending on states)
private:
	void MoveUp();
	void MoveDown();
};

