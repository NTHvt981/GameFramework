#pragma once
#include <list>
#include "CollisionEvent.h"
#include "..\Constraints.h"
#include "..\GraphicAndSound\Graphic.h"
#include "..\Collision\Collision.h"
#include "..\GameObject\GameObject.h"
#include "..\Vector\Vector.h"
#include "..\Library\TextureLibrary.h"

using namespace std;

//Basic collision box, this type are not support for moving
class CCollisionBox
{
protected:
	int id;

	float left;
	float top;
	float right;
	float bottom;

	bool solid = true;

	LPGameObject owner;
	//this list must not contain self collision box instance
	list<LPCollisionBox> coCollisionBoxes;

private:
	static int countId;

public:
	CCollisionBox(LPGameObject obj, 
		float l = 0, float t = 0, float r = 0, float b = 0);

	void RemoveCoBox(LPCollisionBox lpBox);
	void AddCoBox(LPCollisionBox lpBox);

	//Check this if you plan to change how camera work
	void Render();
public:
	float GetLeft();
	float GetTop();
	float GetRight();
	float GetBottom();
	LPGameObject GetOwner();
	bool IsSolid();
	int GetId();

public:
	void GetCollision(list<CollisionEvent>& events);
	bool IsColliding(LPCollisionBox box);

	bool IsHypothesizedColliding(float x, float y);

	void SetLTRB(float l, float t, float r, float b);
	void GetLTRB(float& l, float& t, float& r, float& b);
	void SetSolid(bool _solid);
};

bool CheckCollision(LPCollisionBox a, LPCollisionBox b);