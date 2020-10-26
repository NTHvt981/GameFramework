#include "Orb.h"

COrb::COrb() : CEntity()
{
	SetType(GOTYPES::Enemy);

	this->collisionBox = new CDynamicBox(
		this,
		0, 0,
		18, 18
	);

	moveLeftAni = new CAnimation(1, 100);
	moveRightAni = new CAnimation(1, 100);
	turnLeftAni = new CAnimation(1, 50, 1, false);
	turnRightAni = new CAnimation(1, 50, 1, false);

	moveLeftAni->Add(ID_ORB_1);
	moveRightAni->Add(ID_ORB_5);

	turnRightAni->Add(ID_ORB_1);
	turnRightAni->Add(ID_ORB_2);
	turnRightAni->Add(ID_ORB_3);
	turnRightAni->Add(ID_ORB_4);
	turnRightAni->Add(ID_ORB_5);

	turnLeftAni->Add(ID_ORB_5);
	turnLeftAni->Add(ID_ORB_4);
	turnLeftAni->Add(ID_ORB_3);
	turnLeftAni->Add(ID_ORB_2);
	turnLeftAni->Add(ID_ORB_1);
}

void COrb::Update(DWORD dt)
{
	GetState(dt);

	position = position + velocity;
	collisionBox->Update();
}

void COrb::Render()
{
	currentAni->Render(position);
	collisionBox->Render();
}

void COrb::SetState()
{
}

void COrb::GetState(DWORD dt)
{
	switch (horizontalState)
	{
	case ORB_MOVE_RIGHT:
		MoveRight(dt);
		break;
	case ORB_MOVE_LEFT:
		MoveLeft(dt);
		break;
	case ORB_TURN_LEFT:
		TurnLeft(dt);
		break;
	case ORB_TURN_RIGHT:
		TurnRight(dt);
		break;
	}
}

void COrb::MoveLeft(DWORD dt)
{
	velocity.x = -speed * dt;
	currentAni = moveLeftAni;

	if (position.x <= 10)
	{
		turnRightAni->Reset();
		horizontalState = ORB_TURN_RIGHT;
	}
}

void COrb::MoveRight(DWORD dt)
{
	velocity.x = speed * dt;
	currentAni = moveRightAni;

	if (position.x >= 200)
	{
		turnLeftAni->Reset();
		horizontalState = ORB_TURN_LEFT;
	}
}

void COrb::TurnLeft(DWORD dt)
{
	velocity.x = 0;
	currentAni = turnLeftAni;

	if (currentAni->IsEnd())
		horizontalState = ORB_MOVE_LEFT;
}

void COrb::TurnRight(DWORD dt)
{
	velocity.x = 0;
	currentAni = turnRightAni;

	if (currentAni->IsEnd())
		horizontalState = ORB_MOVE_RIGHT;
}
