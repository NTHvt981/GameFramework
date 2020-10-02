#include "CollisionBox.h"

CCollisionBox::CCollisionBox(LPEntity _gameObject,
	float _localX, float _localY, float width, float height)
{
	entity = _gameObject;
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
}

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
	left = entity->GetPosition().x + localPosition.x;
	top = entity->GetPosition().y + localPosition.y;

	right = left + size.x;
	bottom = top + size.y;
}

void CCollisionBox::Render()
{
	D3DXVECTOR3 position(
		left, top, 0);
	D3DXVECTOR3 origin(0, 0, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextureLibrary::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;
	l = 0;
	t = 0;
	r = right - left;
	b = bottom- top;

	CGraphic::Instance->Draw(bbox, position.x, position.y, l, t, r, b, 0, 0, 0.2);
}

void CCollisionBox::CalculateCollision(Vector& velocity, list<LPEntity>& objectsCollide)
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

LPEntity CCollisionBox::GetGameObject()
{
	return entity;
}
