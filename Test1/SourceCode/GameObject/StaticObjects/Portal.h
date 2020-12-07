#pragma once
#include "../Entity.h"
#include "../../AreaAndScene/Area.h"

#include "../../Player/Player.h"

class CAreaPortal: public CEntity
{
private:
	CArea* area = NULL;
	int areaId;
	int targetId;
	bool alreadyCollideWithPlayer = false;

	Vector direction;
	float distance = 16;
public:
	CAreaPortal(float l, float t, float r, float b, int p=NULL, int a=0);
	void SetTargetId(int t);
	int GetTargetId();

	void SetArea(CArea* area);
	CArea* GetArea();

	void SetAreaId(int area);
	int GetAreaId();

	void Update(DWORD dt);
	void Render();

	bool IsCollideWithPlayer();
	void SetIsCollideWithPlayer(bool b);

	void GetDeployPosition(float &x, float &y);

	void GetLTRB(float& l, float& t, float& r, float& b);
	void SetLTRB(float l, float t, float r, float b);

	float GetDistance();
	void SetDistance(float d);

	void SetDeployDirection(float x, float y);
};

