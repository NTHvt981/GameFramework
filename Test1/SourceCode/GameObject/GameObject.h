#pragma once
#include "../Constraints.h"

enum class GOTYPES
{
	GameObject,
	Entity,
	Static,
	Wall,
	BreakableWall,
	Dynamic,
	Ladder,

	Enemy,
	EnemyBullet,

	Player,
	PlayerBullet,

	//jason is the pilot, and sophia is the tank
	Jason,
	Sophia,
	FakeSophia,

	AreaPortal,
	ScenePortal,
};

class CGameObject
{
protected:
	int state;
	bool visible = true;
	bool enable = true;

private:
	GOTYPES Type = GOTYPES::GameObject;

public:
	CGameObject();
	void Disable();
	void Enable();

	void Pause();
	void Unpause();

	virtual void Update(DWORD dt);
	virtual void Render();
	GOTYPES GetType();

protected:
	void SetType(GOTYPES _type);
};

