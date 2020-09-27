#pragma once
#include <list>
#include "..\Constraints.h"
#include "..\Collision\Collision.h"
#include "..\GameObject\GameObject.h"
#include "..\Vector\Vector.h"

using namespace std;

class CCollisionBox
{
private:
	Vector localPosition;
	Vector size;

	float left = 0;
	float top = 0;
	float right = 0;
	float bottom = 0;

	LPGameObject gameObject;
	//this list must not contain self collision box instance
	list<LPCollisionBox> collisionBoxes;

public:
	//CCollisionBox(LPGameObject _gameObject);
	CCollisionBox(LPGameObject _gameObject, float _localX, float _localY, float width, float height);
	//CCollisionBox(LPGameObject _gameObject, Vector pos, Vector size);

	void RemoveCoBox(LPCollisionBox lpBox);
	void AddCoBox(LPCollisionBox lpBox);

	void Update();
	void CalculateCollision(Vector& velocity, list<LPGameObject> &objectsCollide);
public:
	float GetLeft();
	float GetTop();
	float GetRight();
	float GetBottom();
	LPGameObject GetGameObject();
};

