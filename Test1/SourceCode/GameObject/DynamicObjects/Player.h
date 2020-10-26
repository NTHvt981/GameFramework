#pragma once

#include "../Entity.h"
#include "../Physic.h"
#include "../../Constraints.h"
#include "../../Camera/Camera.h"
#include "../../Input/Input.h"
#include "../../Unit/Animation.h"

#define PLAYER_MOVE_LEFT -1
#define PLAYER_DONT_MOVE 0
#define PLAYER_MOVE_RIGHT 1

#define PLAYER_ON_GROUND 0
#define PLAYER_ON_AIR 1

#define PLAYER_AIM_LEFT 0
#define PLAYER_AIM_RIGHT 1
#define PLAYER_AIM_UPLEFT 2
#define PLAYER_AIM_UPRIGHT 3

class CPlayer: public CEntity, public IPhysic
{
private:
	float speed = 1.5;
	CCamera* camera;

	Vector old_velocity;

	Vector leftWheelPivot = Vector(-8, -4);
	Vector rightWheelPivot = Vector(8, -4);
	Vector headPivot = Vector(0, 3);
	Vector canonPivot = Vector(0, 6);
	Vector bodyPivot = Vector(0, -3);

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
};

