#pragma once

#include "GameObject.h"
#include "..\Constraints.h"
#include "..\Graphic\Graphic.h"
#include "..\Library\TextureLibrary.h"
#include "..\Collision\DynamicBox.h"
#include "..\Collision\CollisionEvent.h"

class CEntity: public CGameObject {
protected:
	int id;
	Vector position;
	Vector origin;
	Vector velocity;

	int speed;

	LPDynamicBox collisionBox = NULL;
	list<CollisionEvent> collideEvents;

protected:
	void move(DWORD dt);

public:
	CEntity();
	void SetPosition(float _x, float _y);
	void SetId(int _id);
	Vector GetPosition();
	int GetId();

	LPDynamicBox GetCollisionBox();

	bool IsCollidedWith(GOTYPES type);
	bool GetCollidedWith(GOTYPES type, list<LPGameObject> &collidedObjs);

	void Update(DWORD dt);
	void Render();

	~CEntity();
};

