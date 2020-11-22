#include "Walker.h"

CWalker::CWalker() : CEntity()
{
	SetType(GOTYPES::Enemy);

	this->collisionBox = new CDynamicBox(
		this,
		0, 0,
		18, 17
	);

	moveDownAni = new CAnimation(1, 200);
	moveUpAni = new CAnimation(1, 200);

	moveDownAni->Add(ID_WALKER_1);
	moveDownAni->Add(ID_WALKER_2);
	moveDownAni->Add(ID_WALKER_4);
	moveDownAni->Add(ID_WALKER_3);

	moveUpAni->Add(ID_WALKER_3);
	moveUpAni->Add(ID_WALKER_4);
	moveUpAni->Add(ID_WALKER_2);
	moveUpAni->Add(ID_WALKER_1);
}

void CWalker::Update(DWORD dt)
{
	GetState(dt);

	position = position + velocity;
	collisionBox->Update();
}

void CWalker::Render()
{
	currentAni->Render(position);
	collisionBox->Render();
}

void CWalker::SetState()
{
}

void CWalker::GetState(DWORD dt)
{
	switch (verticalState)
	{
	case WALKER_MOVE_UP:
		MoveUp(dt);
		break;
	case WALKER_MOVE_DOWN:
		MoveDown(dt);
		break;
	}
}

void CWalker::MoveDown(DWORD dt)
{
	velocity.y = -speed * dt;

	currentAni = moveDownAni;

	if (position.y < 10)
		verticalState = WALKER_MOVE_UP;
}

void CWalker::MoveUp(DWORD dt)
{
	velocity.y = speed * dt;

	currentAni = moveUpAni;

	if (position.y > 200)
		verticalState = WALKER_MOVE_DOWN;
}

void CWalker::DontMove(DWORD dt)
{
	velocity.x = 0;
}

