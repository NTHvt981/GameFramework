#include "Dome.h"

CDome::CDome() : CEntity()
{
	SetType(GOTYPES::Enemy);

	this->collisionBox = new CDynamicBox(
		this,
		0, 0,
		18, 18
	);
	collisionBox->SetSolid(false);

	// dome up
	domeUpMoveLeft = new CAnimation(1, 100);
	int idsUL[] = {
		ID_DOME_UP_MOVE_LEFT_1,
		ID_DOME_UP_MOVE_LEFT_2
	};

	domeUpMoveLeft->Add(idsUL, 2);

	domeUpMoveRight = new CAnimation(1, 100);
	int idsUR[] = {
		ID_DOME_UP_MOVE_RIGHT_1,
		ID_DOME_UP_MOVE_RIGHT_2
	};

	domeUpMoveRight->Add(idsUR, 2);

	// dome down
	domeDownMoveLeft = new CAnimation(1, 100);
	int idsDL[] = {
		ID_DOME_DOWN_MOVE_LEFT_1,
		ID_DOME_DOWN_MOVE_LEFT_2
	};

	domeDownMoveLeft->Add(idsDL, 2);

	domeDownMoveRight = new CAnimation(1, 100);
	int idsDR[] = {
		ID_DOME_DOWN_MOVE_RIGHT_1,
		ID_DOME_DOWN_MOVE_RIGHT_2
	};

	domeDownMoveRight->Add(idsDR, 2);

	// dome left
	domeLeftMoveUp = new CAnimation(1, 100);
	int idsLU[] = {
		ID_DOME_LEFT_MOVE_UP_1,
		ID_DOME_LEFT_MOVE_UP_2
	};

	domeLeftMoveUp->Add(idsLU, 2);

	domeLeftMoveDown = new CAnimation(1, 100);
	int idsLD[] = {
		ID_DOME_LEFT_MOVE_DOWN_1,
		ID_DOME_LEFT_MOVE_DOWN_2
	};

	domeLeftMoveDown->Add(idsLD, 2);

	// dome right
	domeRightMoveUp = new CAnimation(1, 100);
	int idsRU[] = {
		ID_DOME_RIGHT_MOVE_UP_1,
		ID_DOME_RIGHT_MOVE_UP_2
	};

	domeRightMoveUp->Add(idsRU, 2);

	domeRightMoveDown = new CAnimation(1, 100);
	int idsRD[] = {
		ID_DOME_RIGHT_MOVE_DOWN_1,
		ID_DOME_RIGHT_MOVE_DOWN_2
	};

	domeRightMoveDown->Add(idsRD, 2);

	facialState = DOME_UP_MOVE_RIGHT;
	flyingState = DOME_CLING;
}

void CDome::Update(DWORD dt)
{
	GetState(dt);

	position = position + velocity;
	collisionBox->Update();
}

void CDome::Render()
{
	switch (facialState)
	{
	case DOME_UP_MOVE_LEFT:
		domeUpMoveLeft->Render(position);
		break;
	case DOME_UP_MOVE_RIGHT:
		domeUpMoveRight->Render(position);
		break;
	case DOME_DOWN_MOVE_LEFT:
		domeDownMoveLeft->Render(position);
		break;
	case DOME_DOWN_MOVE_RIGHT:
		domeDownMoveRight->Render(position);
		break;
	case DOME_LEFT_MOVE_UP:
		domeLeftMoveUp->Render(position);
		break;
	case DOME_LEFT_MOVE_DOWN:
		domeLeftMoveDown->Render(position);
		break;
	case DOME_RIGHT_MOVE_UP:
		domeRightMoveUp->Render(position);
		break;
	case DOME_RIGHT_MOVE_DOWN:
		domeRightMoveDown->Render(position);
		break;
	default:
		domeUpMoveLeft->Render(position);
		break;
		break;
	}
	collisionBox->Render();
}

void CDome::SetState()
{
}

void CDome::GetState(DWORD dt)
{
	switch (facialState)
	{
	case DOME_UP_MOVE_LEFT:
		MoveLeft(dt);
		break;
	case DOME_UP_MOVE_RIGHT:
		MoveRight(dt);
		break;
	case DOME_DOWN_MOVE_LEFT:
		MoveLeft(dt);
		break;
	case DOME_DOWN_MOVE_RIGHT:
		MoveRight(dt);
		break;
	case DOME_LEFT_MOVE_UP:
		MoveUp(dt);
		break;
	case DOME_LEFT_MOVE_DOWN:
		MoveDown(dt);
		break;
	case DOME_RIGHT_MOVE_UP:
		MoveUp(dt);
		break;
	case DOME_RIGHT_MOVE_DOWN:
		MoveDown(dt);
		break;
	default:
		MoveLeft(dt);
		break;
	}
}

void CDome::MoveLeft(DWORD dt)
{
	velocity.x = -speed * dt;
	velocity.y = 0;

	if (position.y <= 50 && position.x <= 50)
	{
		position.y = 50;
		position.x = 50;
		facialState = DOME_RIGHT_MOVE_UP;
	}

	if (position.y >= 150 && position.x <= 50)
	{
		position.y = 150;
		position.x = 50;
		facialState = DOME_RIGHT_MOVE_DOWN;
	}

	if (position.y <= 50)
	{
		domeUpMoveLeft->SetMode(ANIMATION_NORMAL);
		domeUpMoveRight->SetMode(ANIMATION_REVERSE);
		domeDownMoveLeft->SetMode(ANIMATION_PAUSE);
		domeDownMoveRight->SetMode(ANIMATION_PAUSE);
	}
	else if (position.y >= 150)
	{
		domeUpMoveLeft->SetMode(ANIMATION_PAUSE);
		domeUpMoveRight->SetMode(ANIMATION_PAUSE);
		domeDownMoveLeft->SetMode(ANIMATION_NORMAL);
		domeDownMoveRight->SetMode(ANIMATION_REVERSE);
	}
	domeLeftMoveUp->SetMode(ANIMATION_PAUSE);
	domeLeftMoveDown->SetMode(ANIMATION_PAUSE);
	domeRightMoveUp->SetMode(ANIMATION_PAUSE);
	domeRightMoveDown->SetMode(ANIMATION_PAUSE);
}

void CDome::MoveRight(DWORD dt)
{
	velocity.x = speed * dt;
	velocity.y = 0;

	if (position.y <= 50 && position.x >= 150)
	{
		position.y = 50;
		position.x = 150;
		facialState = DOME_LEFT_MOVE_UP;
	}

	if (position.y >= 150 && position.x >= 150)
	{
		position.y = 150;
		position.x = 150;
		facialState = DOME_LEFT_MOVE_DOWN;
	}

	if (position.y <= 50)
	{
		domeUpMoveLeft->SetMode(ANIMATION_REVERSE);
		domeUpMoveRight->SetMode(ANIMATION_NORMAL);
		domeDownMoveLeft->SetMode(ANIMATION_PAUSE);
		domeDownMoveRight->SetMode(ANIMATION_PAUSE);
	}
	else if (position.y >= 150)
	{
		domeUpMoveLeft->SetMode(ANIMATION_PAUSE);
		domeUpMoveRight->SetMode(ANIMATION_PAUSE);
		domeDownMoveLeft->SetMode(ANIMATION_REVERSE);
		domeDownMoveRight->SetMode(ANIMATION_NORMAL);
	}
	domeLeftMoveUp->SetMode(ANIMATION_PAUSE);
	domeLeftMoveDown->SetMode(ANIMATION_PAUSE);
	domeRightMoveUp->SetMode(ANIMATION_PAUSE);
	domeRightMoveDown->SetMode(ANIMATION_PAUSE);
}

void CDome::MoveUp(DWORD dt)
{
	velocity.y = speed * dt;
	velocity.x = 0;

	if (position.x <= 50 && position.y >= 150)
	{
		position.x = 50;
		position.y = 150;
		facialState = DOME_DOWN_MOVE_RIGHT;
	}

	if (position.x >= 150 && position.y >= 150)
	{
		position.x = 150;
		position.y = 150;
		facialState = DOME_DOWN_MOVE_LEFT;
	}

	if (position.x <= 50)
	{
		domeLeftMoveUp->SetMode(ANIMATION_PAUSE);
		domeLeftMoveDown->SetMode(ANIMATION_PAUSE);
		domeRightMoveUp->SetMode(ANIMATION_NORMAL);
		domeRightMoveDown->SetMode(ANIMATION_REVERSE);
	}
	else if (position.x >= 150)
	{
		domeLeftMoveUp->SetMode(ANIMATION_NORMAL);
		domeLeftMoveDown->SetMode(ANIMATION_REVERSE);
		domeRightMoveUp->SetMode(ANIMATION_PAUSE);
		domeRightMoveDown->SetMode(ANIMATION_PAUSE);
	}

	domeUpMoveLeft->SetMode(ANIMATION_PAUSE);
	domeUpMoveRight->SetMode(ANIMATION_PAUSE);
	domeDownMoveLeft->SetMode(ANIMATION_PAUSE);
	domeDownMoveRight->SetMode(ANIMATION_PAUSE);
}

void CDome::MoveDown(DWORD dt)
{
	velocity.y = -speed * dt;
	velocity.x = 0;

	if (position.x <= 50 && position.y <= 50)
	{
		position.x = 50;
		position.y = 50;
		facialState = DOME_UP_MOVE_RIGHT;
	}

	if (position.x >= 150 && position.y <= 50)
	{
		position.x = 150;
		position.y = 50;
		facialState = DOME_UP_MOVE_LEFT;
	}

	if (position.x <= 50)
	{
		domeLeftMoveUp->SetMode(ANIMATION_PAUSE);
		domeLeftMoveDown->SetMode(ANIMATION_PAUSE);
		domeRightMoveUp->SetMode(ANIMATION_REVERSE);
		domeRightMoveDown->SetMode(ANIMATION_NORMAL);
	}
	else if (position.x >= 150)
	{
		domeLeftMoveUp->SetMode(ANIMATION_REVERSE);
		domeLeftMoveDown->SetMode(ANIMATION_NORMAL);
		domeRightMoveUp->SetMode(ANIMATION_PAUSE);
		domeRightMoveDown->SetMode(ANIMATION_PAUSE);
	}

	domeUpMoveLeft->SetMode(ANIMATION_PAUSE);
	domeUpMoveRight->SetMode(ANIMATION_PAUSE);
	domeDownMoveLeft->SetMode(ANIMATION_PAUSE);
	domeDownMoveRight->SetMode(ANIMATION_PAUSE);
}

void CDome::Fly(DWORD dt)
{
	velocity.x = speed * dt;
	velocity.y = speed * dt;

	domeLeftMoveUp->SetMode(ANIMATION_PAUSE);
	domeLeftMoveDown->SetMode(ANIMATION_PAUSE);
	domeRightMoveUp->SetMode(ANIMATION_PAUSE);
	domeRightMoveDown->SetMode(ANIMATION_PAUSE);
	domeUpMoveLeft->SetMode(ANIMATION_PAUSE);
	domeUpMoveRight->SetMode(ANIMATION_PAUSE);
	domeDownMoveLeft->SetMode(ANIMATION_PAUSE);
	domeDownMoveRight->SetMode(ANIMATION_PAUSE);
}

void CDome::DontMove(DWORD dt)
{
	velocity.x = 0;
	velocity.y = 0;

	domeLeftMoveUp->SetMode(ANIMATION_PAUSE);
	domeLeftMoveDown->SetMode(ANIMATION_PAUSE);
	domeRightMoveUp->SetMode(ANIMATION_PAUSE);
	domeRightMoveDown->SetMode(ANIMATION_PAUSE);
	domeUpMoveLeft->SetMode(ANIMATION_PAUSE);
	domeUpMoveRight->SetMode(ANIMATION_PAUSE);
	domeDownMoveLeft->SetMode(ANIMATION_PAUSE);
	domeDownMoveRight->SetMode(ANIMATION_PAUSE);
}
