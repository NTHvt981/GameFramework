#pragma once
#include "Constraints.h"
#include "Core/Vector.h"
#include "Entity.h"
#include "Sprite.h"
#include "Animation.h"

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

	int64_t realSophiaId;

	void Render();

private:
	static CSophiaFake* __instance;
public:
	static CSophiaFake* GetInstance();
};

