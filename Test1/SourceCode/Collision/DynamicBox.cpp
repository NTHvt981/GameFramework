#include "DynamicBox.h"

void CDynamicBox::Update()
{
	left = entity->GetPosition().x + localPosition.x;
	bottom = entity->GetPosition().y + localPosition.y;
	
	right = left + size.x;
	top = bottom - size.y;
}

void CDynamicBox::Follow(float x, float y)
{
	left = x + localPosition.x;
	bottom = y + localPosition.y;

	right = left + size.x;
	top = bottom - size.y;
}

void CDynamicBox::CalculateCollision(Vector& velocity, list<CollisionEvent>& events)
{
	events.clear();
	CCollision::GetInstance()->GetCollisionBoxes(id, collisionBoxes);

	//SweptBroadphaseBox
	float broadLeft, broadRight, broadTop, broadBottom;
	CCollision::GetInstance()->GetSweptBroadphaseBox(
		left, top, right, bottom,
		velocity.x, velocity.y,
		broadLeft, broadTop, broadRight, broadBottom
	);

	for each (LPCollisionBox staticBox in collisionBoxes)
	{
		//get left, top, right, bottom of other collision boxes
		float staticLeft, staticTop, staticRight, staticBottom;
		staticLeft = staticBox->GetLeft();
		staticTop = staticBox->GetTop();
		staticRight = staticBox->GetRight();
		staticBottom = staticBox->GetBottom();

		//if false -> no Collision garantee
		if (CCollision::GetInstance()->AABBCheck(
			broadLeft, broadTop, broadRight, broadBottom,
			staticLeft, staticTop, staticRight, staticBottom
		))
		{
			float collideTime, normalX, normalY;

			CCollision::GetInstance()->SweptAABB(
				left, top, right, bottom,
				velocity.x, velocity.y,
				staticLeft, staticTop, staticRight, staticBottom,
				collideTime, normalX, normalY
			);

			//if there is collision
			if (collideTime < 1.0f && collideTime >= 0.0f && (!(normalX==0 && normalY==0)))
			{
				//asign the game object that contain collision box
				events.push_back(
					{
						staticBox->GetOwner(),
						Vector(normalX, normalY)
					});

				// if both this box and collide box are solid
				// recalculate the velocity
				if (solid && staticBox->IsSolid())
				{
					float newX, newY;
					CCollision::GetInstance()->Slide(
						left, top,
						newX, newY,
						velocity.x, velocity.y,
						collideTime, normalX, normalY
					);

					velocity.x = newX - left;
					velocity.y = newY - top;
				}
			}
		}
	}
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
