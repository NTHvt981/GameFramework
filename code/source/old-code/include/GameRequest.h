#pragma once

#include "Constraints.h"
#include "Scene.h"

enum GAME_REQUEST_TYPES
{
	SwitchToIntro,
	SwitchToSideScroll,
	SwitchToTopDown,
	SwitchToBoss,
	SwitchToEnding
};

class CGameRequest
{
public:
	static std::list<LPGameRequest> RequestList;

	//fields
public:
	GAME_REQUEST_TYPES Type;
	SCENE_TYPES sender;

	float x = -1;
	float y = -1;

	//method
public:
	CGameRequest(GAME_REQUEST_TYPES t);
	static void AddRequest(LPGameRequest re);
};

