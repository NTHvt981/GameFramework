#pragma once
#include "../Constraints.h"
#include "../Vector/Vector.h"
#include "../GameObject/Entity.h"
#include "../Unit/Sprite.h"
#include "../Unit/Animation.h"

class CSophiaFake: public CEntity
{
public:
	CSophiaFake();

	Vector headPivot;
	Vector canonPivot;
	Vector leftWheelPivot;
	Vector rightWheelPivot;
	Vector bodyPivot;

	LPAnimation leftWheelAni;
	LPAnimation rightWheelAni;

	LPSprite headSprite;
	LPSprite canonSprite;
	LPSprite bodySprite;

	int realSophiaId;

	void Render();

private:
	static CSophiaFake* __instance;
public:
	static CSophiaFake* GetInstance();
};

