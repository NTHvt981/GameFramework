#pragma once
#include "../Constraints.h"

enum class GOTYPES
{
	GameObject,
	Entity,
	Static,
	Wall,
	Dynamic,
	Porter,
	Ladder,

	Enemy,
	EnemyBullet,

	Player,
	PlayerBullet,

	//jason is the pilot, and sophia is the tank
	Jason,
	Sophia,
	FakeSophia
};

class CGameObject
{
protected:
	int state;
	bool visible = true;
	bool enable = true;

private:
	GOTYPES type = GOTYPES::GameObject;

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

