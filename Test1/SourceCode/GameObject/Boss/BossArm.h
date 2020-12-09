#pragma once

#include "../../Constraints.h"
#include "../Entity.h"

#include "../../Unit/Sprite.h"
#include "../../Library/SpriteLibrary.h"

class CBossArm: public CEntity
{
private:
	const float maxDistance = 20;
	CBossArm* child;
	bool isTheEnd = false;

	int width, height;

	LPSprite sprite = NULL;

public:
	bool* isStretchAll = NULL;

public:
	CBossArm(bool *_isStretchAll, CBossArm* _armBeforeIt, bool isTheHead, int sprId);

protected:
	void Move(DWORD dt);

public:
	void MoveCallFromParent(DWORD dt, float _x, float _y);
	void MoveCallFromBoss(DWORD dt, float _x, float _y);
	void Render();
	void SetPosition(float _x, float _y);

public:
	void SetIsStretchAllAddress(bool* _isStretchAll);
};

