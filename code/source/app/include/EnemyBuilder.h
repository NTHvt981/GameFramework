#pragma once

#include "Enemy.h"
#include "Constraints.h"

#include "Canon.h"
#include "Dasher.h"
#include "Dome.h"
#include "EyeBall.h"
#include "Floater.h"
#include "Head.h"
#include "Insect.h"
#include "Jumper.h"
#include "Mine.h"
#include "Orb.h"
#include "Skull.h"
#include "Spiral.h"
#include "Teleporter.h"
#include "Walker.h"
#include "Worm.h"

#define CANON_HEALTH 5
#define DASHER_HEALTH 1
#define DOME_HEALTH 3
#define EYEBALL_HEALTH 3
#define FLOATER_HEALTH 5
#define HEAD_HEALTH 9
#define INSECT_HEALTH 3
#define JUMPER_HEALTH 3
#define MINE_HEALTH 5
#define ORB_HEALTH 5
#define SKULL_HEALTH 1
#define SPIRAL_HEALTH 5
#define TELEPORTER_HEALTH 3
#define WALKER_HEALTH 3
#define WORM_HEALTH 1

class CEnemyBuilder
{
public:
	static LPEnemy Create(ENEMY_TYPE type, int64_t param=0);
};