#include "DynamicBox.h"

void CDynamicBox::Update()
{
	this->Follow(entity->GetPosition().x, entity->GetPosition().y);
}

void CDynamicBox::Follow(float x, float y)
{
	left = x + localPosition.x;
	top = y + localPosition.y;

	right = left + size.x;
	bottom = top + size.y;
}

void CDynamicBox::CalculateCollision(Vector& velocity, list<CollisionEvent>& events)
{

	//SweptBroadphaseBox
	float broadLeft, broadRight, broadTop, broadBottom;
	GetSweptBroadphaseBox(
		left, top, right, bottom,
		velocity.x, velocity.y,
		broadLeft, broadTop, broadRight, broadBottom
	);

	for each (LPCollisionBox staticBox in coCollisionBoxes)
	{
		//get left, top, right, bottom of other collision boxes
		float staticLeft, staticTop, staticRight, staticBottom;
		staticBox->GetLTRB(staticLeft, staticTop, staticRight, staticBottom);

		//if false -> there is no collision
		if (AABBCheck(
			broadLeft, broadTop, broadRight, broadBottom,
			staticLeft, staticTop, staticRight, staticBottom
		))
		{
			float collideTime, normalX, normalY;

			SweptAABB(
				left, top, right, bottom,
				velocity.x, velocity.y,
				staticLeft, staticTop, staticRight, staticBottom,
				collideTime, normalX, normalY
			);

			//this doesnt work with player vs enemies
			//if there is collision
			if (collideTime < 1.0f && collideTime >= 0.0f && 
				(!(normalX==0 && normalY==0)))
			{
				//asign the game object that contain collision box
				events.push_back(
					{
						staticBox->GetOwner(),
						Vector(normalX, normalY)
					});

				// if other box is solid
				// recalculate the velocity
				if (staticBox->IsSolid())
				{
					float newX, newY;
					Slide(
						left, top,
						newX, newY,
						velocity.x, velocity.y,
						collideTime, normalX, normalY
					);

					velocity.x = newX - left;
					velocity.y = newY - top;
				}
			}
			
			//this is temporary code
			//not recommend
			else
			{
				if (AABBCheck(
					left, top, right, bottom,
					staticLeft, staticTop, staticRight, staticBottom
				))
					//asign the game object that contain collision box
					events.push_back(
						{
							staticBox->GetOwner(),
							Vector(0, 0)
						});

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

void CDynamicBox::ResetCoCollisionBoxes(
	list<LPCollisionBox> newCoCollisionBoxes)
{
	for each (LPCollisionBox oldBoxes in coCollisionBoxes) {
		oldBoxes->RemoveCoBox(this);
	}

	coCollisionBoxes.clear();

	for each (LPCollisionBox newBox in newCoCollisionBoxes) {
		if (newBox->GetId() != this->id)
		{
			//add self to new box co boxes
			newBox->AddCoBox(this);

			//add new box to self co collision boxes
			AddCoBox(newBox);
		}
	}
}

Vector CDynamicBox::GetSize()
{
	return this->size;
}

Vector CDynamicBox::GetLocalPosition()
{
	return localPosition;
}