#pragma once
#include <list>
#include "..\Constraints.h"
#include "..\Graphic\Graphic.h"
#include "..\Collision\Collision.h"
#include "..\GameObject\GameObject.h"
#include "..\Vector\Vector.h"
#include "..\Library\TextureLibrary.h"

using namespace std;

//Basic collision box, this type are not support for moving
class CCollisionBox
{
protected:
	float left;
	float top;
	float right;
	float bottom;

	bool solid = true;

	LPGameObject owner;
	//this list must not contain self collision box instance
	list<LPCollisionBox> collisionBoxes;

public:
	CCollisionBox(LPGameObject obj, float l = 0, float t = 0, float r = 0, float b=0);

	void RemoveCoBox(LPCollisionBox lpBox);
	void AddCoBox(LPCollisionBox lpBox);

	void Render();
	void CalculateCollision(Vector& velocity, 
		list<LPGameObject> &objectsCollide);
public:
	float GetLeft();
	float GetTop();
	float GetRight();
	float GetBottom();
	LPGameObject GetOwner();
	bool IsSolid();

public:
	void SetLTRB(float l, float t, float r, float b);
	void SetSolid(bool _solid);
};

