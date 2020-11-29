#pragma once

#include "../GameObject/Entity.h"
#include "../Constraints.h"
#include "../Camera/Camera.h"
#include "../Input/Input.h"
#include "../Unit/Animation.h"
#include "PlayerHealth.h"
#include "PlayerBullet.h"

#include "../Game/GameRequest.h"

class CPlayer: public CEntity
{
protected:
	float speed = 1.5;
	CCamera* camera;
	Vector old_velocity;

	/// <summary>
	/// these vars for being damaged animation
	/// </summary>
	bool healthAniWhiteFlip = false;
	DWORD healthAniWaitTime = 10;
	DWORD healthAniCountTime = 0;
	int addUpSpriteId;

	/// <summary>
	/// these vars for shooting funtion
	/// </summary>
	bool canShoot = true;
	DWORD shootWaitTime = 15;
	DWORD shootCountTime = 0;


private:
	static CPlayer* currentPlayer;

protected:
	virtual void SetState(DWORD dt);
	virtual void GetState(DWORD dt);

public:
	CPlayer();
	virtual void Update(DWORD dt);
	virtual void Render();

	static CPlayer* GetCurrentPlayer();
	static void SetCurrentPlayer(CPlayer* player);

protected:
	virtual void SetHealthAnimation(DWORD dt);

	void HandleShooting(DWORD dt);
	virtual void Shoot();
};

