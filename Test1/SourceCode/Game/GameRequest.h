#pragma once

#include "../Constraints.h"
#include "../GameObject/Entity.h"

enum REQUEST_TYPES
{
	CreateEntity,
	DeleteEntity,
	SetEnetity
};

class CGameRequest
{
	//fields
public:
	REQUEST_TYPES type;
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
	CGameRequest(REQUEST_TYPES t);
};

