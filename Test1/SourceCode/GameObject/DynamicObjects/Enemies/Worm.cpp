#include "Worm.h"

CWorm::CWorm() : CEntity()
{
	SetType(GOTYPES::Enemy);
	gravity = 0.25;

	this->collisionBox = new CDynamicBox(
		this,
		0, 0,
		18, 10
	);

	crawlLeftAni = new CAnimation(1, 200);
	int idsL[] = {
		ID_WORM_MOVE_LEFT_1,
		ID_WORM_MOVE_LEFT_2
	};

	crawlLeftAni->Add(idsL, 2);

	crawlRightAni = new CAnimation(1, 200);
	int idsR[] = {
		ID_WORM_MOVE_RIGHT_1,
		ID_WORM_MOVE_RIGHT_2
	};

	crawlRightAni->Add(idsR, 2);

	horizontalState = WORM_MOVE_RIGHT;
}

void CWorm::Update(DWORD dt)
{
	GetState(dt);

	velocity.y -= gravity;
	move(dt);

	collisionBox->Update();
}

void CWorm::Render()
{
	if (horizontalState == WORM_MOVE_RIGHT)
	{
		crawlRightAni->Render(position);
	}
	else if (horizontalState == WORM_MOVE_LEFT)
	{
			crawlLeftAni->Render(position);
	}
	collisionBox->Render();
}

void CWorm::SetState()
{
}

void CWorm::GetState(DWORD dt)
{
	switch (horizontalState)
	{
	case WORM_MOVE_RIGHT:
		MoveRight(dt);
		break;
	case WORM_MOVE_LEFT:
		MoveLeft(dt);
		break;
	case WORM_DONT_MOVE:
		DontMove(dt);
		break;
	}
}

void CWorm::MoveLeft(DWORD dt)
{
	velocity.x = -speed * dt;

	if (position.x <= 10)
	{
		horizontalState = WORM_MOVE_RIGHT;
	}

	crawlLeftAni->SetMode(ANIMATION_NORMAL);
	crawlRightAni->SetMode(ANIMATION_REVERSE);
}

void CWorm::MoveRight(DWORD dt)
{
	velocity.x = speed * dt;

	if (position.x >= 320)
	{
		horizontalState = WORM_MOVE_LEFT;
	}

	crawlLeftAni->SetMode(ANIMATION_REVERSE);
	crawlRightAni->SetMode(ANIMATION_NORMAL);
}

void CWorm::DontMove(DWORD dt)
{
	velocity.x = 0;

	crawlLeftAni->SetMode(ANIMATION_PAUSE);
	crawlRightAni->SetMode(ANIMATION_PAUSE);
}
