#include "Area.h"

CArea::CArea(float l, float t, float r, float b)
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}

void CArea::GetLTRB(float& l, float& t, float& r, float& b)
{
	l = left;
	t = top;
	r = right;
	b = bottom;
}
