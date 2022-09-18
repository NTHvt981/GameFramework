#pragma once

#include "GameObject.h"
#include "Constraints.h"
#include "DynamicBox.h"
#include "CollisionEvent.h"

class CEntity: public CGameObject {
protected:
	int64_t id;
	Vector position;
	Vector origin;
	Vector velocity;

	int64_t gridX = -1;
	int64_t gridY = -1;

	int64_t speed;

	LPDynamicBox collisionBox = NULL;
	std::list<CollisionEvent> collideEvents;

	//for physic
	bool onGround = false;
	float gravity = 0;
	float jumpSpeed = 0;

protected:
	virtual void Move(DWORD dt);
	virtual void MoveWithoutGravity(DWORD dt);

public:
	CEntity();
	int64_t GetId() const;
	void SetId(int64_t _id);

	virtual void SetPosition(float _x, float _y);
	virtual Vector GetPosition();
	virtual void SetCenter(float _x, float _y);
	virtual Vector GetCenter();

	LPDynamicBox GetCollisionBox();

	bool IsCollidedWith(GOTYPES Type);
	bool GetCollidedWith(GOTYPES Type, std::list<LPGameObject> &collidedObjs);

	bool IsColliding(LPEntity entity);

	void Update(DWORD dt);
	void Render();

	~CEntity();

	void GetGridPosition(int64_t &x, int64_t &y);
	void SetGridPosition(int64_t x, int64_t y);
};

bool CheckCollision(LPEntity a, LPEntity b);

