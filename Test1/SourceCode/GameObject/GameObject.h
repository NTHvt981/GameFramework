#pragma once
#include "../Constraints.h"

class CGameObject
{
protected:
	int state;
	//GOTYPES type = GOTYPES::GameObject;

public:
	virtual void Update(DWORD dt);
	virtual void Render();
};

//enum class GOTYPES
//{
//	GameObject,
//	Entity,
//	Static,
//	Dynamic,
//	Player,
//	Enemy
//};

