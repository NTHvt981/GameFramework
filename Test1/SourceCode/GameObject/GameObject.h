#pragma once
#include "../Constraints.h"

enum class GOTYPES
{
	GameObject,
	Entity,
	Static,
	Ground,
	Wall,
	Dynamic,
	Player,
	Enemy
};

class CGameObject
{
protected:
	int state;
private:
	GOTYPES type = GOTYPES::GameObject;

public:
	virtual void Update(DWORD dt);
	virtual void Render();
	GOTYPES GetType();

protected:
	void SetType(GOTYPES _type);
};

