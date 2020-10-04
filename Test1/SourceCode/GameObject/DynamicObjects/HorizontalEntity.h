#pragma once

#include "../Entity.h"
#include "../../Constraints.h"

class CHorizontalEntity: public CEntity
{
public:
	CHorizontalEntity(LPCWSTR texturePath);
	void Update(DWORD dt);

	//state functions (get called depending on states)
private:
	void MoveLeft();
	void MoveRight();
};


