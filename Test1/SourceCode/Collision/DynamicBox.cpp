#include "DynamicBox.h"

void CDynamicBox::Update()
{
	left = entity->GetPosition().x + localPosition.x;
	bottom = entity->GetPosition().y + localPosition.y;
	
	right = left + size.x;
	top = bottom - size.y;
}

CDynamicBox::CDynamicBox(LPEntity _entity, float _localX, float _localY, float width, float height)
	:CCollisionBox(_entity)
{
	entity = _entity;
	localPosition.x = _localX;
	localPosition.y = _localY;

	size.x = width;
	size.y = height;

}
