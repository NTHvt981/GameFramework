#include "Jumper.h"

CJumper::CJumper(LPCWSTR texturePath) : CEntity(texturePath)
{
	SetType(GOTYPES::Enemy);

	this->collisionBox = new CDynamicBox(
		this,
		0, 0,
		17, 26
	);

	moveLeftAni = new CAnimation(1, 150);
	int idsL[] = {
		ID_JUMPER_MOVE_LEFT_1,
		ID_JUMPER_MOVE_LEFT_2,
		ID_JUMPER_MOVE_LEFT_3
	};

	moveLeftAni->Add(idsL, 3);

	moveRightAni = new CAnimation(1, 150);
	int idsR[] = {
		ID_JUMPER_MOVE_RIGHT_1,
		ID_JUMPER_MOVE_RIGHT_2,
		ID_JUMPER_MOVE_RIGHT_3
	};

	moveRightAni->Add(idsR, 3);

	horizontalState = JUMPER_MOVE_RIGHT;
}

void CJumper::Update(DWORD dt)
{
	GetState(dt);

	position = position + velocity;
	collisionBox->Update();
}

void CJumper::Render()
{
	if (horizontalState == JUMPER_MOVE_LEFT)
	{
		moveLeftAni->Render(position);
	}
	else if (horizontalState == JUMPER_MOVE_RIGHT)
	{
		moveRightAni->Render(position);
	}
	collisionBox->Render();
}

void CJumper::SetState()
{
}

void CJumper::GetState(DWORD dt)
{
	switch (horizontalState)
	{
	case JUMPER_MOVE_RIGHT:
		MoveRight(dt);
		break;
	case JUMPER_MOVE_LEFT:
		MoveLeft(dt);
		break;
	case JUMPER_DONT_MOVE:
		DontMove(dt);
		break;
	}
}

void CJumper::MoveLeft(DWORD dt)
{
	velocity.x = -speed * dt;

	if (position.x <= 50)
	{
		horizontalState = JUMPER_MOVE_RIGHT;
	}
}

void CJumper::MoveRight(DWORD dt)
{
	velocity.x = speed * dt;

	if (position.x >= 320)
	{
		horizontalState = JUMPER_MOVE_LEFT;
	}
}

void CJumper::DontMove(DWORD dt)
{
	velocity.x = 0;

	moveLeftAni->SetMode(ANIMATION_PAUSE);
	moveRightAni->SetMode(ANIMATION_PAUSE);
}
