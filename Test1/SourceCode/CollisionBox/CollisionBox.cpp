#include "CollisionBox.h"

CCollisionBox::CCollisionBox(LPGameObject _gameObject, 
	float _localX, float _localY, float width, float height)
{
	gameObject = _gameObject;
	localPosition.x = _localX;
	localPosition.y = _localY;

	size.x = width;
	size.y = height;

	CCollision::GetInstance()->GetCollisionBoxes();
	for each (LPCollisionBox box in CCollision::GetInstance()->GetCollisionBoxes())
	{
		collisionBoxes.push_back(box);
		box->AddCoBox(this);
	}
	CCollision::GetInstance()->AddCollisionBox(this);

	DebugOut(L"[DEBUG] number of co collision boxes %d\n", collisionBoxes.size());
}

//CCollisionBox::CCollisionBox(LPGameObject _gameObject, Vector _pos, Vector _size)
//{
//	gameObject = _gameObject;
//	localPosition.x = _pos.x;
//	localPosition.y = _pos.y;
//
//	size.x = _size.x;
//	size.y = _size.y;
//}

void CCollisionBox::RemoveCoBox(LPCollisionBox lpBox)
{
	try
	{
		collisionBoxes.remove(lpBox);
	}
	catch (const std::exception& ex)
	{
		DebugOut(L"[ERROR] remove collision box, exception code %s", *ex.what());
	}
}

void CCollisionBox::AddCoBox(LPCollisionBox lpBox)
{
	collisionBoxes.push_back(lpBox);
}

void CCollisionBox::Update()
{
	left = gameObject->GetPosition().x + localPosition.x;
	top = gameObject->GetPosition().y + localPosition.y;

	right = left + size.x;
	bottom = top + size.y;
}

void CCollisionBox::CalculateCollision(Vector& velocity, list<LPGameObject>& objectsCollide)
{
	objectsCollide.clear();

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
			if (collideTime < 1.0f && collideTime >= 0.0f)
			{
				//asign the game object that contain collision box
				objectsCollide.push_back(staticBox->GetGameObject());

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

float CCollisionBox::GetLeft()
{
	return left;
}

float CCollisionBox::GetTop()
{
	return top;
}

float CCollisionBox::GetRight()
{
	return right;
}

float CCollisionBox::GetBottom()
{
	return bottom;
}

LPGameObject CCollisionBox::GetGameObject()
{
	return LPGameObject();
}
