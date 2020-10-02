#pragma once
#include <list>
#include "..\Constraints.h"
#include "..\Graphic\Graphic.h"
#include "..\Collision\Collision.h"
#include "..\GameObject\Entity.h"
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

	LPEntity entity;
	//this list must not contain self collision box instance
	list<LPCollisionBox> collisionBoxes;

public:
	//CCollisionBox(LPGameObject _gameObject);
	CCollisionBox(LPEntity _gameObject, float _localX, float _localY, float width, float height);
	//CCollisionBox(LPGameObject _gameObject, Vector pos, Vector size);

	void RemoveCoBox(LPCollisionBox lpBox);
	void AddCoBox(LPCollisionBox lpBox);

	void Update();
	void Render();
	void CalculateCollision(Vector& velocity, list<LPEntity> &objectsCollide);
public:
	float GetLeft();
	float GetTop();
	float GetRight();
	float GetBottom();
	LPEntity GetGameObject();
};

