#pragma once

#include "Constraints.h"
#include "SpriteLibrary.h"
#include "Timer.h"
#include "Player.h"

#include "Input.h"

#include "SoundLibrary.h"

#define VULNERABLE 0
#define INVULNERABLE 1

#define SOPHIA 0
#define JASON 1

class CPlayerHealth
{
private:
	static CPlayerHealth* __instance;
	int64_t sophiaHealth;
	int64_t sophiaMaxHealth = 10;

	int64_t jasonHealth;
	int64_t jasonMaxHealth = 10;

	int64_t healthState = VULNERABLE;
	int64_t playerMode = SOPHIA;

	CTimer *invulnerableTimer;

	bool gameOver = false;

	//these vars for rendering
	Vector drawPosition = Vector(0, 0);

	LPSprite sprTextHov;
	LPSprite sprTextPow;
	LPSprite sprSophiaHealthBar;
	LPSprite sprJasonHealthBar;

	Vector textHovPivot = Vector(25, 250);
	Vector textHealthBarPivot = Vector(25, 375);
	Vector textPowPivot = Vector(25, 400);

private:
	void turnOnInvulnerability();
	void turnOffInvulnerability();

	void ReduceSophiaHealth(int64_t damage = 1);
	void IncreaseSophiaHealth(int64_t heal_points = 1);

	void ReduceJasonHealth(int64_t damage = 1);
	void IncreaseJasonHealth(int64_t heal_points = 1);

public:
	CPlayerHealth();
	static CPlayerHealth* GetInstance();
	void Restart();

	void ReduceHealth(GOTYPES Type, int64_t damage = 1);
	void ReduceHealth(int64_t damage = 1);
	void IncreaseHealth(GOTYPES Type, int64_t heal_points = 1);
	void IncreaseHealth(int64_t heal_points = 1);

	void SetPlayerMode(int64_t _mode);
	int64_t GetHealthState();

	bool IsGameOver();

	void Update(DWORD dt);
	void Render();

	//this section for cheating
private:
	bool cheat = false;
	void SetCheat(DWORD dt);
};

