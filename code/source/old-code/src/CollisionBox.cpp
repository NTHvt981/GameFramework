#include "CollisionBox.h"

int64_t CCollisionBox::countId = 0;

CCollisionBox::CCollisionBox(LPGameObject obj, float l, float t, float r, float b)
{
	//Set id
	id = countId;
	countId++;

	left = l;
	top = t;
	right = r;
	bottom = b;

	owner = obj;

	CCollision::GetInstance()->AddCollisionBox(this);
}

void CCollisionBox::RemoveCoBox(LPCollisionBox lpBox)
{
	try
	{
		coCollisionBoxes.remove(lpBox);
	}
	catch (const std::exception& ex)
	{
		DebugOut(L"[ERROR] remove collision box, exception code %s", *ex.what());
	}
}

void CCollisionBox::AddCoBox(LPCollisionBox lpBox)
{
	coCollisionBoxes.push_back(lpBox);
}

void CCollisionBox::Render()
{
	D3DXVECTOR3 position(
		left, top, 0);
	D3DXVECTOR3 origin(0, 0, 0);

	LPDIRECT3DTEXTURE9 bbox = CTextureLibrary::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;
	l = 0;
	t = 0;
	r = right - left;
	b = bottom- top;

	CGraphic::Instance->Draw(bbox, position.x, position.y, l, t, r, b, 0, 0, 0.2);
}

float CCollisionBox::GetLeft() const
{
	return left;
}

float CCollisionBox::GetTop() const
{
	return top;
}

float CCollisionBox::GetRight() const
{
	return right;
}

float CCollisionBox::GetBottom() const
{
	return bottom;
}

LPGameObject CCollisionBox::GetOwner() const
{
	return owner;
}

bool CCollisionBox::IsSolid() const
{
	return solid;
}

int64_t CCollisionBox::GetId() const
{
	return id;
}

void CCollisionBox::GetCollision(std::list<CollisionEvent>& events)
{
	events.clear();

	for (const LPCollisionBox& staticBox: coCollisionBoxes)
	{
		//get left, top, right, bottom of other collision boxes
		float staticLeft, staticTop, staticRight, staticBottom;
		staticLeft = staticBox->GetLeft();
		staticTop = staticBox->GetTop();
		staticRight = staticBox->GetRight();
		staticBottom = staticBox->GetBottom();

		//if false -> garantee no Collision
		if (AABBCheck(
			left, top, right, bottom,
			staticLeft, staticTop, staticRight, staticBottom
		))
		{
			events.push_back({ staticBox->GetOwner(), Vector(0, 0) });
		}
	}
}

bool CCollisionBox::IsColliding(LPCollisionBox box)
{
	//get left, top, right, bottom of other collision boxes
	float staticLeft, staticTop, staticRight, staticBottom;
	staticLeft = box->GetLeft();
	staticTop = box->GetTop();
	staticRight = box->GetRight();
	staticBottom = box->GetBottom();

	//if false -> garantee no Collision
	return AABBCheck(
		left, top, right, bottom,
		staticLeft, staticTop, staticRight, staticBottom
	);
}

bool CCollisionBox::IsHypothesizedColliding(float x, float y)
{
	float hypLeft, hypTop, hypRight, hypBottom;

	hypLeft = x;
	hypTop = y;
	hypRight = x + (right - left);
	hypBottom = y + (bottom - top);

	for (const LPCollisionBox& staticBox : coCollisionBoxes)
	{
		//get left, top, right, bottom of other collision boxes
		float staticLeft, staticTop, staticRight, staticBottom;
		staticLeft = staticBox->GetLeft();
		staticTop = staticBox->GetTop();
		staticRight = staticBox->GetRight();
		staticBottom = staticBox->GetBottom();

		//if false -> garantee no Collision
		if (AABBCheck(
			hypLeft, hypTop, hypRight, hypBottom,
			staticLeft, staticTop, staticRight, staticBottom
		) && staticBox->IsSolid())
		{
			return true;
		}
	}

	return false;
}

void CCollisionBox::SetLTRB(float l, float t, float r, float b)
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}

void CCollisionBox::GetLTRB(float &l, float &t, float &r, float &b)
{
	l = left;
	t = top;
	r = right;
	b = bottom;
}

void CCollisionBox::SetSolid(bool _solid)
{
	this->solid = _solid;
}

bool CheckCollision(LPCollisionBox a, LPCollisionBox b)
{
	float al, at, ar, ab;
	float bl, bt, br, bb;

	a->GetLTRB(al, at, ar, ab);
	b->GetLTRB(bl, bt, br, bb);

	return AABBCheck(al, at, ar, ab, bl, bt, br, bb);
}
