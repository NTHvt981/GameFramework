#include "Collision.h"

CCollision* CCollision::__instance = NULL;

CCollision* CCollision::GetInstance() {
	if (__instance == NULL) __instance = new CCollision();
	return __instance;
}

void CCollision::SweptAABB(
	float move_left, float move_top, float move_right, float move_bottom,
	float move_velocity_x, float move_velocity_y,
	float static_left, float static_top, float static_right, float static_bottom,
	float& collide_time,
	float& normal_x,
	float& normal_y)
{
	float entry_x, entry_y;
	float exit_x, exit_y;
	/*
	what is entry and exit, look at this
  move_l		 move_r	   static_l			static_r
	|	  move		|			|	 static		|
					<---entry--->
	<-------------------exit-------------------->
	this illustrate the horizontal axis
	the same can be said for the vertical axis
	*/

	if (move_velocity_x > 0.0f)
	{
		entry_x = static_left - move_right;
		exit_x = static_right - static_left;
	}
	else
	{
		entry_x = static_right - static_left;
		exit_x = static_left - move_right;
	}

	if (move_velocity_y > 0.0f)
	{
		entry_y = static_top - move_bottom;
		exit_y = static_bottom - move_top;
	}
	else
	{
		entry_y = static_bottom - move_top;
		exit_y = static_top - move_bottom;
	}

	// find time of collision and time of leaving for
	// each axis(if statement is to prevent divide by zero)
	float entry_time_x, entry_time_y;
	float exit_time_x, exit_time_y;

	//we will devide entry position to velocity to get the entry time
	//for x entry_x / velocity_x
	//what if velocity == 0 ? asign entry time to infinity
	//the same goes for exit time, exit position
	if (move_velocity_x == 0.0f)
	{
		entry_time_x = -std::numeric_limits<float>::infinity();
		exit_time_x = std::numeric_limits<float>::infinity();
	}
	else
	{
		entry_time_x = entry_x / move_velocity_x;
		exit_time_x = exit_x / move_velocity_x;
	}

	if (move_velocity_y == 0.0f)
	{
		entry_time_y = -std::numeric_limits<float>::infinity();
		exit_time_y = std::numeric_limits<float>::infinity();
	}
	else
	{
		entry_time_y = entry_y / move_velocity_y;
		exit_time_y = exit_y / move_velocity_y;
	}

	float entry_time = max(entry_time_x, entry_time_y);
	float exit_time = min(exit_time_x, exit_time_y);

	// if there was no collision
	if (entry_time > exit_time ||
		entry_x < 0.0f && entry_y < 0.0f ||
		entry_x > 1.0f || entry_y > 1.0f)
		//collide time return 0 -> no collision
	{
		normal_x = 0.0f;
		normal_y = 0.0f;
		collide_time = 1.0f;
	}
	else //I dont understand these line
	{
		if (entry_time_x > entry_time_y)
		{
			if (entry_x < 0.0f)
			{
				normal_x = 1.0f;
				normal_y = 0.0f;
			}
			else
			{
				normal_x = -1.0f;
				normal_y = 0.0f;
			}
		}
		else
		{
			if (entry_y < 0.0f)
			{
				normal_x = 0.0f;
				normal_y = 1.0f;
			}
			else
			{
				normal_x = 0.0f;
				normal_y = -1.0f;
			}
		}
	}
}
