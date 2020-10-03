#include "Ground.h"

CGround::CGround(float l, float t, float r, float b) : CWall(l, t, r, b) {
	SetType(GOTYPES::Ground);
}
