#include "Player.h"

CPlayer* CPlayer::currentPlayer = NULL;

CPlayer::CPlayer(): CEntity()
{
	SetType(GOTYPES::Player);
}

void CPlayer::Update(DWORD dt)
{
	if (!enable) return;
	if (CPlayer::GetCurrentPlayer()->GetId() != GetId()) return;

}

void CPlayer::Render()
{
	if (!visible) return;
}

CPlayer* CPlayer::GetCurrentPlayer()
{
	return currentPlayer;
}

void CPlayer::SetCurrentPlayer(CPlayer* player)
{
	currentPlayer = player;
}

void CPlayer::SetState(DWORD dt)
{
}

void CPlayer::GetState(DWORD dt)
{
}

void CPlayer::SetHealthAnimation(DWORD dt)
{
}

void CPlayer::HandleShooting(DWORD dt)
{
	CInput* input = CInput::GetInstance();

	if (!canShoot)
	{
		shootCountTime = min(shootCountTime + dt, shootWaitTime);
		if (shootCountTime >= shootWaitTime) canShoot = true;
	}
	else
	{
		if (keyShoot)
		{
			//DebugOut(L"[INFO] SHOOT\n");
			Shoot();
		}
	}
}

void CPlayer::Shoot()
{
}
