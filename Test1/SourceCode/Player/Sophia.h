#pragma once
#include "Player.h"

#define SOPHIA_MOVE_LEFT -1
#define SOPHIA_DONT_MOVE 0
#define SOPHIA_MOVE_RIGHT 1

#define SOPHIA_ON_GROUND 0
#define SOPHIA_ON_AIR 1

#define SOPHIA_AIM_LEFT 0
#define SOPHIA_AIM_RIGHT 1
#define SOPHIA_AIM_UPLEFT 2
#define SOPHIA_AIM_UPRIGHT 3

//state for side
#define ON_LEFT 0
#define ON_RIGHT 1
#define ON_LEFT_TURN_RIGHT 2
#define ON_RIGHT_TURN_LEFT 3
#define ON_LEFT_EJECT_JASON 4
#define ON_RIGHT_EJECT_JASON 5

//state for facing
#define FACE_UP_LEFT 0
#define FACE_UP_RIGHT 1
#define FACE_LEFT 2
#define FACE_RIGHT 3

//states for pace
#define MOVE_LEFT 1
#define MOVE_RIGHT 2
#define STILL 3

class CSophia :
    public CPlayer
{
private:
	/// <summary>
	/// these vars for shooting funtion
	/// </summary>
	Vector shootLeftPivot = Vector(0, 10);
	Vector shootRightPivot = Vector(16, 10);
	Vector shootUpLeftPivot = Vector(17, -2);
	Vector shootUpRightPivot = Vector(9, -2);

	Vector ejectJasonLeftPivot = Vector(15, 13);
	Vector ejectJasonRightPivot = Vector(14, 13);

	Vector* headPivot;
	Vector* canonPivot;
	Vector* leftWheelPivot;
	Vector* rightWheelPivot;
	Vector* bodyPivot;

	/*
	standing is then sophia aim canon upward
	*/
	Vector leftWheelOnGroundPivot = Vector(4, 18);
	Vector rightWheelOnGroundPivot = Vector(18, 18);
	Vector leftWheelStandingPivot = Vector(6, 18);
	Vector rightWheelStandingPivot = Vector(16, 18);

	/*
	On ground when sophia (tank) is on the ground
	On air is when sophia jump

	position y of head, body, canon of sophia -2 when on air

	*/
	Vector bodyOnGroundPivot = Vector(12, 18);
	Vector bodyStandingPivot = Vector(11, 13);

	Vector leftCanonPivot = Vector(3, 12);
	Vector rightCanonPivot = Vector(20, 12);
	Vector upLeftCanonPivot = Vector(17, 0);
	Vector upRightCanonPivot = Vector(9, 0);

	Vector leftHeadPivot = Vector(10, 10);
	Vector rightHeadPivot = Vector(4, 10);
	Vector upRightHeadPivot = Vector(0, 6);
	Vector upLeftHeadPivot = Vector(15, 6);

	//Vector center = Vector(0, 0);

	LPAnimation leftWheelAni;
	LPAnimation rightWheelAni;

	LPSprite headSprite;
	LPSprite canonSprite;
	LPSprite bodySprite;

	int state = ON_RIGHT;
	int prevState = state;
	int nextState = state;
	int face = FACE_RIGHT;
	int pace = STILL;
	bool showCanon = true;

private:
	//keys for input
	bool keyLeft;
	bool keyUp;
	bool keyRight;
	bool keyDown;
	bool keyJump;
	bool keyShoot;
	bool keySwitchPlayer;

	void onLeft(DWORD dt);
	void onRight(DWORD dt);
	void onLeftTurnRight(DWORD dt);
	void onRightTurnLeft(DWORD dt);
	void onLeftEjectJason(DWORD dt);
	void onRightEjectJason(DWORD dt);

protected:
	void SetState(DWORD dt);
	void GetState(DWORD dt);

public:
	CSophia();
	void Update(DWORD dt);
	void Render();

protected:
	void SetHealthAnimation(DWORD dt);

	void Shoot();
};

