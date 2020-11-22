#pragma once

#include "../GameObject/Entity.h"
#include "../Constraints.h"
#include "../Camera/Camera.h"
#include "../Input/Input.h"
#include "../Unit/Animation.h"
#include "PlayerHealth.h"
#include "PlayerBullet.h"

#include "../Game/Game.h"

#define PLAYER_MOVE_LEFT -1
#define PLAYER_DONT_MOVE 0
#define PLAYER_MOVE_RIGHT 1

#define PLAYER_ON_GROUND 0
#define PLAYER_ON_AIR 1

#define PLAYER_AIM_LEFT 0
#define PLAYER_AIM_RIGHT 1
#define PLAYER_AIM_UPLEFT 2
#define PLAYER_AIM_UPRIGHT 3

class CPlayer: public CEntity
{
private:
	float speed = 1.5;
	CCamera* camera;

	/// <summary>
	/// these vars for being damaged animation
	/// </summary>
	bool healthAniWhiteFlip = false;
	DWORD healthAniWaitTime = 10;
	DWORD healthAniCountTime = 0;
	int addUpSpriteId;

	/// <summary>
	/// these vars for shooting funtion
	/// </summary>
	Vector leftShootPivot = Vector(0, 12);
	Vector rightShootPivot = Vector(16, 12);
	Vector upLeftShootPivot = Vector(17, -4);
	Vector upRightShootPivot = Vector(9, -4);
	bool canShoot = true;
	DWORD shootWaitTime = 15;
	DWORD shootCountTime = 0;

	Vector old_velocity;

	Vector* headPivot;
	Vector* canonPivot;
	Vector* leftWheelPivot;
	Vector* rightWheelPivot;
	Vector* bodyPivot;

	/*
	standing is then sophia aim canon upward
	*/
	Vector leftWheelOnGroundPivot	= Vector(4, 18);
	Vector rightWheelOnGroundPivot	= Vector(18, 18);
	Vector leftWheelStandingPivot = Vector(6, 18);
	Vector rightWheelStandingPivot = Vector(16, 18);

	/*
	On ground when sophia (tank) is on the ground
	On air is when sophia jump

	position y of head, body, canon of sophia -2 when on air

	*/
	Vector bodyOnGroundPivot	= Vector(12, 18);
	Vector bodyOnAirPivot		= Vector(12, 16);
	Vector bodyStandingPivot	= Vector(11, 13);
	Vector bodyStandingInAirPivot = Vector(11, 11);

	Vector leftCanonPivot		= Vector(3, 12);
	Vector rightCanonPivot		= Vector(20, 12);
	Vector upLeftCanonPivot		= Vector(17, 0);
	Vector upRightCanonPivot	= Vector(9, 0);
	
	Vector leftCanonOnAirPivot		= Vector(3, 10);
	Vector rightCanonOnAirPivot		= Vector(20, 10);
	Vector upLeftCanonOnAirPivot	= Vector(17, -2);
	Vector upRightCanonOnAirPivot	= Vector(9, -2);

	Vector leftHeadPivot	= Vector(10, 10);
	Vector rightHeadPivot	= Vector(4, 10);
	Vector upRightHeadPivot = Vector(0, 6);
	Vector upLeftHeadPivot	= Vector(15, 6);

	//Vector center = Vector(0, 0);

	LPAnimation leftWheelAni;
	LPAnimation rightWheelAni;

	LPSprite headSprite;
	LPSprite bodySprite;
	LPSprite canonSprite;

	int horizontalState = PLAYER_DONT_MOVE;
	int verticalState = PLAYER_ON_GROUND;
	int aimDirection = PLAYER_AIM_RIGHT;

private:
	static CPlayer* currentPlayer;

private:
	void SetState();
	void GetState();

	void MoveLeft();
	void MoveRight();
	void StandStill();

	void AimLeft();
	void AimRight();
	void AimUpLeft();
	void AimUpRight();

public:
	CPlayer();
	void Update(DWORD dt);
	void Render();

	static CPlayer* GetCurrentPlayer();
	static void SetCurrentPlayer(CPlayer* player);

protected:
	//this function is only called for debug
	void move(DWORD dt);
	void SetHealthAnimation(DWORD dt);

	void HandleShooting(DWORD dt);
	void Shoot(int aim_direction);
};

