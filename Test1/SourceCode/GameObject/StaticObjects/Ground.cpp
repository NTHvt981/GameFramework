#include "Ground.h"

CGround::CGround(float l, float t, float r, float b, bool solid) : CWall(l, t, r, b) {
	SetType(GOTYPES::Ground);
	collisionBox->SetSolid(solid);
}
