#pragma once

#include "../Constraints.h"
#include "../GameObject/Entity.h"
#include <list>

using namespace std;

enum SCENE_REQUEST_TYPES
{
	CreateEntity,
	DeleteEntity,
	SetEntity,

	SwitchToJason,
	SwitchToSophia,

	SwitchArea,
};

class CSceneRequest
{
public:
	static list<LPSceneRequest> RequestList;

	//fields
public:
	SCENE_REQUEST_TYPES Type;
	int id = -1;

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

