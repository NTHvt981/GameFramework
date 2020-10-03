#pragma once

#include "..\Entity.h"

class CWall: public CEntity
{
protected:
	GOTYPES type = GOTYPES::Static;
protected:
	void move(DWORD dt);
public:
	CWall(float l, float t, float r, float b);
	void Render();
};

