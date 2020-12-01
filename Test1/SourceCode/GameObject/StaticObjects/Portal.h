#pragma once
#include "../Entity.h"
#include "../../AreaAndScene/Area.h"

class CPortal: public CEntity
{
private:
	CArea* area = NULL;
	int areaId;
	int targetId;
	bool alreadyCollideWithPlayer = false;
public:
	CPortal(float l, float t, float r, float b, int p=NULL);
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

	Vector localDeployPosition = Vector(-16, 12);
	void SetDeploySide(int s);
	void GetDeployPosition(float &x, float &y);
};

