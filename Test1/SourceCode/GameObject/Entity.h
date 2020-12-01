#pragma once

#include "GameObject.h"
#include "..\Constraints.h"
#include "..\Collision\DynamicBox.h"
#include "..\Collision\CollisionEvent.h"

class CEntity: public CGameObject {
protected:
	int id;
	Vector position;
	Vector origin;
	Vector velocity;

	Vector gridPosition = Vector(-1, -1);

	int speed;

	LPDynamicBox collisionBox = NULL;
	list<CollisionEvent> collideEvents;

	//for physic
	bool onGround = false;
	float gravity = 0;
	float jumpSpeed = 0;

protected:
	virtual void Move(DWORD dt);
	virtual void MoveWithoutGravity(DWORD dt);

public:
	CEntity();
	int GetId();
	void SetId(int _id);

	virtual void SetPosition(float _x, float _y);
	virtual Vector GetPosition();
	virtual void SetCenter(float _x, float _y);
	virtual Vector GetCenter();

	LPDynamicBox GetCollisionBox();

	bool IsCollidedWith(GOTYPES type);
	bool GetCollidedWith(GOTYPES type, list<LPGameObject> &collidedObjs);

	void Update(DWORD dt);
	void Render();

	~CEntity();

	void GetGridPosition(int &x, int &y);
	void SetGridPosition(int x, int y);
};

bool CheckCollision(LPEntity a, LPEntity b);

