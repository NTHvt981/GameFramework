#pragma once

#include "../Enemies/Enemy.h"
#include "../Physic.h"
#include "../../Constraints.h"

#include "../../Library/SpriteLibrary.h"
#include "../../Unit/Sprite.h"
#include "../../Unit/Animation.h"

#include "BossArm.h"
#include "BossHand.h"

class CBoss : public CEnemy
{
private:
	bool* gameOver;
	LPAnimation animation;

	int width, height;

	const Vector leftHandPivot = Vector(-30, -8);
	const Vector rightHandPivot = Vector(30, -8);

	CBossHand *leftHand;
	CBossHand *rightHand;

	/// <summary>
	/// FOR DEBUG
	/// </summary>
	vector<Vector> debugMatrix;
	int index = 0;

public:
	CBoss(bool *overCon);
	void Update(DWORD dt);
	void Render();
	void SetCenter(float _x, float _y);
};

