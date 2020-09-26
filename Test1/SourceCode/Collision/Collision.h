#pragma once

#include "..\Constraints.h"

class CCollision
{
private:
	static CCollision* __instance;
public:
	static CCollision* GetInstance();
public:
	//vital functions for game object to use
	static void SweptAABB(
		float move_left,
		float move_top,
		float move_right,
		float move_bottom,
		float move_velocity_x,
		float move_velocity_y,
		float static_left,
		float static_top,
		float static_right,
		float static_bottom,
		float& collide_time,
		float& normal_x,
		float& normal_y);
};

