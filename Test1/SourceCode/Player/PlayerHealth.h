#pragma once

#include "../Constraints.h"
#include "../Library/SpriteLibrary.h"
#include "../Timer/Timer.h"
#include "Player.h"

#define VULNERABLE 0
#define INVULNERABLE 1

#define SOPHIA 0
#define JASON 1

class CPlayerHealth
{
private:
	static CPlayerHealth* __instance;
	int sophiaHealth;
	int sophiaMaxHealth = 10;

	int jasonHealth;
	int jasonMaxHealth = 10;

	int healthState = VULNERABLE;
	int playerMode = SOPHIA;

	CTimer *invulnerableTimer;

	bool gameOver = false;

	//these vars for rendering
	Vector drawPosition = Vector(0, 0);

	LPSprite sprTextHov;
	LPSprite sprTextPow;
	LPSprite sprSophiaHealthBar;
	LPSprite sprJasonHealthBar;

	Vector textHovPivot = Vector(25, 225);
	Vector textHealthBarPivot = Vector(25, 350);
	Vector textPowPivot = Vector(25, 375);

private:
	void turnOnInvulnerability();
	void turnOffInvulnerability();

	void ReduceSophiaHealth(int damage = 1);
	void IncreaseSophiaHealth(int heal_points = 1);

	void ReduceJasonHealth(int damage = 1);
	void IncreaseJasonHealth(int heal_points = 1);

public:
	CPlayerHealth();
	static CPlayerHealth* GetInstance();
	void Restart();

	void ReduceHealth(GOTYPES Type, int damage = 1);
	void IncreaseHealth(GOTYPES Type, int heal_points = 1);

	void SetPlayerMode(int _mode);
	int GetHealthState();

	bool IsGameOver();

	void Update(DWORD dt);
	void Render();
};

