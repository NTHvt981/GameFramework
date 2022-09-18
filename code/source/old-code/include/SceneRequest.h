#pragma once

#include "Constraints.h"
#include "Entity.h"
#include <list>



enum SCENE_REQUEST_TYPES
{
	CreateEntity,
	DeleteEntity,
	SetEntity,

	SwitchToJason,
	SwitchToSophia,

	SwitchArea,

	CreateHealthBall,
	CreateEnergyBall,
	CreatePowerBall
};

class CSceneRequest
{
public:
	static std::list<LPSceneRequest> RequestList;

	//fields
public:
	SCENE_REQUEST_TYPES Type;
	int64_t id = -1;

	/// <summary>
	/// these var for create entity
	/// called by entity themself
	/// </summary>
	LPEntity entity;
	float x = -1;
	float y = -1;

	//method
public:
	CSceneRequest(SCENE_REQUEST_TYPES t);
	static void AddRequest(LPSceneRequest re);
};

