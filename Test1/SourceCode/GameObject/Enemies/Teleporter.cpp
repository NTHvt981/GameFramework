#include "Teleporter.h"

CTeleporter::CTeleporter(): CEnemy()
{
	aniVulnerable = new CAnimation(1000);
	aniInvulnerable = new CAnimation(1000);
	aniTransition = new CAnimation(75);

	if (CUtils::lottery(0.5))
	{
		aniVulnerable->Add(ID_TELEPORTER_LEFT_2);
		aniInvulnerable->Add(ID_TELEPORTER_LEFT_1);
		aniTransition->Add(ID_TELEPORTER_LEFT_1);
		aniTransition->Add(ID_TELEPORTER_LEFT_2);
	}
	else
	{
		aniVulnerable->Add(ID_TELEPORTER_RIGHT_2);
		aniInvulnerable->Add(ID_TELEPORTER_RIGHT_1);
		aniTransition->Add(ID_TELEPORTER_RIGHT_1);
		aniTransition->Add(ID_TELEPORTER_RIGHT_2);
	}

	animation = aniInvulnerable;
	state = TELEPORTER_INVULNERABLE;

	animation->GetSize(width, height);
	collisionBox = new CDynamicBox(
		this, 0, 0,
		width, height
	);
	collisionBox->SetSolid(false);
}

void CTeleporter::Update(DWORD dt)
{
	if (InPlayerZone())
		switch (state)
		{
		case TELEPORTER_INVULNERABLE:
			InvulnerableState(dt);
			break;
		case TELEPORTER_VULNERABLE:
			VulnerableState(dt);
			break;
		case TELEPORTER_TRANSITION:
			TransitionState(dt);
			break;
		default:
			break;
		}
}

void CTeleporter::VulnerableState(DWORD dt)
{
	animation = aniVulnerable;

	vulnerableCountUp += dt;

	if (!canTele)
	{
		if (CUtils::lottery(0.05))
			canTele = TeleportToPlayer(dt);
		else
			canTele = TeleportRandom(dt);
	}

	if (vulnerableCountUp >= vulnerableWaitTime / 2 && canTele)
	{
		MoveTo(dt, teleX, teleY);
	}

	if (vulnerableCountUp >= vulnerableWaitTime && canTele)
	{
		canTele = false;

		vulnerableCountUp = 0;
		nextState = TELEPORTER_INVULNERABLE;
		state = TELEPORTER_TRANSITION;
	}
}

void CTeleporter::InvulnerableState(DWORD dt)
{
	animation = aniInvulnerable;

	invulnerableCountUp += dt;
	if (invulnerableCountUp >= invulnerableWaitTime)
	{
		invulnerableCountUp = 0;
		nextState = TELEPORTER_VULNERABLE;
		state = TELEPORTER_TRANSITION;
	}
}

void CTeleporter::TransitionState(DWORD dt)
{
	animation = aniTransition;

	transitionCountUp += dt;
	if (transitionCountUp >= transitionWaitTime)
	{
		transitionCountUp = 0;
		state = nextState;
	}
}

bool CTeleporter::TeleportRandom(DWORD dt)
{
	float l, t, r, b;
	CCamera::GetInstance()->GetOuterBound(l, t, r, b);
	teleX = CUtils::randRange(l, r - width);
	teleY = CUtils::randRange(t, b - height);

	if (collisionBox->IsHypothesizedColliding(
		teleX, teleY
	))
	{
		return false;
	}

	return true;
}

bool CTeleporter::TeleportToPlayer(DWORD dt)
{
	Vector pPos = CPlayer::GetCurrentPlayer()->GetPosition();

	teleX = pPos.x;
	teleY = pPos.y;

	return true;
}

void CTeleporter::Render()
{
	animation->Render(position);
	collisionBox->Render();
}

void CTeleporter::InflictDamage(int dam)
{
	if (state != TELEPORTER_INVULNERABLE)
		CEnemy::InflictDamage(dam);
}

void CTeleporter::Move(DWORD dt)
{
	position.x += velocity.x;
	position.y += velocity.y;
	collisionBox->Update();
}

void CTeleporter::MoveTo(DWORD dt, float x, float y)
{
	position.Set(x, y);
	collisionBox->Update();
}
