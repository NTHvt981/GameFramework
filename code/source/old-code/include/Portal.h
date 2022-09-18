#pragma once
#include "Entity.h"
#include "Area.h"

#include "Player.h"

class CAreaPortal: public CEntity
{
private:
	CArea* area = NULL;
	int64_t areaId;
	int64_t targetId;
	bool alreadyCollideWithPlayer = false;

	Vector direction;
	float distance = 16;
public:
	CAreaPortal(float l, float t, float r, float b, int64_t p=NULL, int64_t a=0);
	void SetTargetId(int64_t t);
	int64_t GetTargetId();

	void SetArea(CArea* area);
	CArea* GetArea() const;

	void SetAreaId(int64_t area);
	int64_t GetAreaId() const;

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

