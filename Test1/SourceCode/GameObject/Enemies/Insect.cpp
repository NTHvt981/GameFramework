#include "Insect.h"

void CInsect::DriftDownState(DWORD dt)
{
	velocity.x = 0;
	velocity.y = driftDownSpeed;

	Move(dt);
	animation->SetSpeed(1);

	stateTime = min(stateTime + dt, driftDownTime);
	if (stateTime == driftDownTime)
	{
		stateTime = 0;
		state = INSECT_BOOST_UP;
	}
}

void CInsect::BoostUpState(DWORD dt)
{
	velocity.x = 0;
	velocity.y = -boostUpSpeed;

	Move(dt);
	animation->SetSpeed(3);

	stateTime = min(stateTime + dt, boostUpTime);
	if (stateTime == boostUpTime)
	{
		stateTime = 0;
		state = INSECT_DRIFT_DOWN;
	}
}

CInsect::CInsect()
{
	SetType(GOTYPES::Enemy);

	leftAni = new CAnimation(300);
	int idsL[] = {
		ID_INSECT_MOVE_LEFT_1,
		ID_INSECT_MOVE_LEFT_2
	};

	leftAni->Add(idsL, 2);

	rightAni = new CAnimation(300);
	int idsR[] = {
		ID_INSECT_MOVE_RIGHT_1,
		ID_INSECT_MOVE_RIGHT_2
	};

	rightAni->Add(idsR, 2);
	animation = rightAni;

	animation->GetSize(width, height);
	this->collisionBox = new CDynamicBox(
		this,
		0, 0,
		width, height
	);
	collisionBox->SetSolid(false);
}

void CInsect::Update(DWORD dt)
{
	switch (state)
	{
	case INSECT_DRIFT_DOWN:
		DriftDownState(dt);
		break;
	case INSECT_BOOST_UP:
		BoostUpState(dt);
		break;
	}
}

void CInsect::Render()
{
	animation->Render(position.x, position.y);
	collisionBox->Render();
}