#pragma once

#include "Enemy.h"
#include "../../Constraints.h"
#include "../../Unit/Animation.h"

#include "../../Debug/Utils.h"

#define TELEPORTER_VULNERABLE 0
#define TELEPORTER_INVULNERABLE 1
#define TELEPORTER_TRANSITION 2

#define TELEPORTER_LEFT 0
#define TELEPORTER_RIGHT 1

class CTeleporter: public CEnemy
{
private:
	LPAnimation aniVulnerable;
	LPAnimation aniInvulnerable;
	LPAnimation aniTransition;
	LPAnimation animation;

	float teleMinRange = 50;
	float teleMaxRange = 100;
	Vector teleDirection = Vector(1, 0);

	int state;
	/// <summary>
	/// either invul or vul state
	/// </summary>
	int nextState;

private:
	bool canTele = false;
	float teleX = 0;
	float teleY = 0;
	DWORD vulnerableCountUp = 0;
	const DWORD vulnerableWaitTime = 60;

	DWORD invulnerableCountUp = 0;
	const DWORD invulnerableWaitTime = 150;

	DWORD transitionCountUp = 0;
	const DWORD transitionWaitTime = 40;

private:
	void VulnerableState(DWORD dt);
	void InvulnerableState(DWORD dt);
	void TransitionState(DWORD dt);
	bool TeleportRandom(DWORD dt);
	bool TeleportToPlayer(DWORD dt);

public:
	CTeleporter();
	void Update(DWORD dt);
	void Render();
	void InflictDamage(int dam);

protected:
	void Move(DWORD dt);
	void MoveTo(DWORD dt, float x, float y);
};

