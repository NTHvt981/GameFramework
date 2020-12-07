#pragma once
#include "../Entity.h"
#include "../../Player/Player.h"

class CTopDownPortal : public CEntity
{
private:
	bool alreadyCollideWithPlayer = false;

public:
	CTopDownPortal(float l, float t, float r, float b);

	void Update(DWORD dt);
	void Render();

	bool IsCollideWithPlayer();
	void SetIsCollideWithPlayer(bool b);

	void GetLTRB(float& l, float& t, float& r, float& b);
	void SetLTRB(float l, float t, float r, float b);
};

