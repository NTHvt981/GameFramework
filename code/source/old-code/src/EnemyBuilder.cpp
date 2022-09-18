#include "EnemyBuilder.h"

LPEnemy CEnemyBuilder::Create(ENEMY_TYPE type, int64_t param)
{
	switch (type)
	{
	case Canon:
		return (new CCanon())->SetMaxHealth(CANON_HEALTH);
		break;
	case Dasher:
		return (new CDasher(param))->SetMaxHealth(DASHER_HEALTH);
		break;
	case Dome:
		return (new CDome())->SetMaxHealth(DOME_HEALTH);
		break;
	case EyeBall:
		return (new CEyeBall(param))->SetMaxHealth(EYEBALL_HEALTH);
		break;
	case Floater:
		return (new CFloater(param))->SetMaxHealth(FLOATER_HEALTH);
		break;
	case Head:
		return (new CHead())->SetMaxHealth(HEAD_HEALTH);
		break;
	case Insect:
		return (new CInsect())->SetMaxHealth(INSECT_HEALTH);
		break;
	case Jumper:
		return (new CJumper())->SetMaxHealth(JUMPER_HEALTH);
		break;
	case Orb:
		return (new COrb())->SetMaxHealth(ORB_HEALTH);
		break;
	case Skull:
		return (new CSkull())->SetMaxHealth(SKULL_HEALTH);
		break;
	case Spiral:
		return (new CSpiral())->SetMaxHealth(SPIRAL_HEALTH);
		break;
	case Teleporter:
		return (new CTeleporter())->SetMaxHealth(TELEPORTER_HEALTH);
		break;
	case Walker:
		return (new CWalker())->SetMaxHealth(WALKER_HEALTH);
		break;
	case Worm:
		return (new CWorm())->SetMaxHealth(WORM_HEALTH);
		break;
	default:
		return NULL;
		break;
	}
}
