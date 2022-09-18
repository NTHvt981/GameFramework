#pragma once
#include <list>
#include "CollisionEvent.h"
#include "Constraints.h"
#include "Graphic.h"
#include "Collision.h"
#include "GameObject.h"
#include "Core/Vector.h"
#include "TextureLibrary.h"



//Basic collision box, this type are not support for moving
class CCollisionBox
{
protected:
	int64_t id;

	float left;
	float top;
	float right;
	float bottom;

	bool solid = true;

	LPGameObject owner;
	//this std::list must not contain self collision box instance
	std::list<LPCollisionBox> coCollisionBoxes;

private:
	static int64_t countId;

public:
	CCollisionBox(LPGameObject obj, 
		float l = 0, float t = 0, float r = 0, float b = 0);

	void RemoveCoBox(LPCollisionBox lpBox);
	void AddCoBox(LPCollisionBox lpBox);

	//Check this if you plan to change how camera work
	void Render();
public:
	float GetLeft() const;
	float GetTop() const;
	float GetRight() const;
	float GetBottom() const;
	LPGameObject GetOwner() const;
	bool IsSolid() const;
	int64_t GetId() const;

public:
	void GetCollision(std::list<CollisionEvent>& events);
	bool IsColliding(LPCollisionBox box);

	bool IsHypothesizedColliding(float x, float y);

	void SetLTRB(float l, float t, float r, float b);
	void GetLTRB(float& l, float& t, float& r, float& b);
	void SetSolid(bool _solid);
};

bool CheckCollision(LPCollisionBox a, LPCollisionBox b);