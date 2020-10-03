#pragma once

#include "../../Constraints.h"
#include "DynamicEntity.h"

class CHorizontalEntity: public CDynamicEntity
{
public:
	CHorizontalEntity(LPCWSTR texturePath);
	void Update(DWORD dt);

	//state functions (get called depending on states)
private:
	void MoveLeft();
	void MoveRight();
};


