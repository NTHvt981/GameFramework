#include "Physic.h"

void IPhysic::ApplyPhysic(Vector& v)
{
	v.y -= gravity;
}
