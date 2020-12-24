#include "Dome.h"
 
void CDome::ClingState(DWORD dt)
{
	bool noGroundCon = !collisionBox->IsHypothesizedColliding(
		position.x + clingDirection.x,
		position.y + clingDirection.y
	);

	bool hitWallCon = collisionBox->IsHypothesizedColliding(
		position.x + clingSpeed * moveDirection.x,
		position.y + clingSpeed * moveDirection.y
	);

	if (noGroundCon)
	{
		Vector temp;
		temp.x = moveDirection.x;
		temp.y = moveDirection.y;

		moveDirection.x = clingDirection.x;
		moveDirection.y = clingDirection.y;

		clingDirection.x = -temp.x;
		clingDirection.y = -temp.y;
	}

	if (hitWallCon)
	{
		Vector temp;
		temp.x = moveDirection.x;
		temp.y = moveDirection.y;

		moveDirection.x = -clingDirection.x;
		moveDirection.y = -clingDirection.y;

		clingDirection.x = temp.x;
		clingDirection.y = temp.y;
	}

	velocity.x = clingSpeed * moveDirection.x;
	velocity.y = clingSpeed * moveDirection.y;

	Move(dt);

	waitTime = min(waitTime + dt, maxWaitTime);
	bool finish = false;
	if (waitTime >= maxWaitTime) finish = true;
	bool mainAxisNear = false;
	bool sideAxisNear = false;

	bool onTheSameSide = false;
	Vector playerPos = CPlayer::GetCurrentPlayer()->GetCenter();
	Vector selfPos = GetCenter();

	//check if meet the player
	if (clingDirection.x != 0)
	{
		if ((playerPos.x - selfPos.x) * (-clingDirection.x) > 0)
			onTheSameSide = true;

		mainAxisNear = HorizontalDistanceToPlayer() < maxMainAxisDistance;
		sideAxisNear = VerticalDistanceToPlayer() < maxSideAxisDistance;
	}
	else
	{
		if ((playerPos.y - selfPos.y) * (-clingDirection.y) > 0)
			onTheSameSide = true;

		mainAxisNear = VerticalDistanceToPlayer() < maxMainAxisDistance;
		sideAxisNear = HorizontalDistanceToPlayer() < maxSideAxisDistance;
	}
	if (mainAxisNear && sideAxisNear && finish && onTheSameSide)
	{
		state = MY_DOME_FLY;
	}
}

void CDome::FlyState(DWORD dt)
{
	velocity.x = -flySpeed * clingDirection.x;
	velocity.y = -flySpeed * clingDirection.y;

	Move(dt);

	bool headButtWallCon = collisionBox->IsHypothesizedColliding(
		position.x - clingDirection.x,
		position.y - clingDirection.y
	);

	if (headButtWallCon) {
		clingDirection.x = -clingDirection.x;
		clingDirection.y = -clingDirection.y;

		waitTime = 0;

		state = MY_DOME_CLING;
	}
}

void CDome::SetInitDirection()
{
	bool noGroundCon = !collisionBox->IsHypothesizedColliding(
		position.x + clingDirection.x,
		position.y + clingDirection.y
	);

	setInitDirection = true;
}

CDome::CDome() : CEnemy()
{
	SetType(GOTYPES::Enemy);

	this->collisionBox = new CDynamicBox(
		this,
		0, 0,
		18, 18
	);
	collisionBox->SetSolid(false);

	// dome up
	domeUpMoveLeft = new CAnimation(100);
	int idsUL[] = {
		ID_DOME_UP_MOVE_LEFT_1,
		ID_DOME_UP_MOVE_LEFT_2
	};

	domeUpMoveLeft->Add(idsUL, 2);

	domeUpMoveRight = new CAnimation(100);
	int idsUR[] = {
		ID_DOME_UP_MOVE_RIGHT_1,
		ID_DOME_UP_MOVE_RIGHT_2
	};

	domeUpMoveRight->Add(idsUR, 2);

	// dome down
	domeDownMoveLeft = new CAnimation(100);
	int idsDL[] = {
		ID_DOME_DOWN_MOVE_LEFT_1,
		ID_DOME_DOWN_MOVE_LEFT_2
	};

	domeDownMoveLeft->Add(idsDL, 2);

	domeDownMoveRight = new CAnimation(100);
	int idsDR[] = {
		ID_DOME_DOWN_MOVE_RIGHT_1,
		ID_DOME_DOWN_MOVE_RIGHT_2
	};

	domeDownMoveRight->Add(idsDR, 2);

	// dome left
	domeLeftMoveUp = new CAnimation(100);
	int idsLU[] = {
		ID_DOME_LEFT_MOVE_UP_1,
		ID_DOME_LEFT_MOVE_UP_2
	};

	domeLeftMoveUp->Add(idsLU, 2);

	domeLeftMoveDown = new CAnimation(100);
	int idsLD[] = {
		ID_DOME_LEFT_MOVE_DOWN_1,
		ID_DOME_LEFT_MOVE_DOWN_2
	};

	domeLeftMoveDown->Add(idsLD, 2);

	// dome right
	domeRightMoveUp = new CAnimation(100);
	int idsRU[] = {
		ID_DOME_RIGHT_MOVE_UP_1,
		ID_DOME_RIGHT_MOVE_UP_2
	};

	domeRightMoveUp->Add(idsRU, 2);

	domeRightMoveDown = new CAnimation(100);
	int idsRD[] = {
		ID_DOME_RIGHT_MOVE_DOWN_1,
		ID_DOME_RIGHT_MOVE_DOWN_2
	};

	domeRightMoveDown->Add(idsRD, 2);

	animation = domeUpMoveRight;
}

void CDome::Update(DWORD dt)
{
	if (!setInitDirection) SetInitDirection();

	switch (state)
	{
	case MY_DOME_CLING:
		ClingState(dt);
		break;
	case MY_DOME_FLY:
		FlyState(dt);
		break;
	}

	if (clingDirection.x == 1 && moveDirection.y == 1)
		animation = domeLeftMoveDown;
	else if (clingDirection.x == 1 && moveDirection.y == -1)
		animation = domeLeftMoveUp;

	if (clingDirection.x == -1 && moveDirection.y == 1)
		animation = domeRightMoveDown;
	else if (clingDirection.x == -1 && moveDirection.y == -1)
		animation = domeRightMoveUp;

	else if (clingDirection.y == 1 && moveDirection.x == 1)
		animation = domeUpMoveRight;
	else if (clingDirection.y == 1 && moveDirection.x == -1)
		animation = domeUpMoveLeft;

	if (clingDirection.y == -1 && moveDirection.x == 1)
		animation = domeDownMoveRight;
	else if (clingDirection.y == -1 && moveDirection.x == -1)
		animation = domeDownMoveLeft;
}

void CDome::Render()
{
	animation->Render(position.x, position.y);
	collisionBox->Render();
}
