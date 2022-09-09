#include "Collision.h"

CCollision* CCollision::__instance = NULL;

CCollision* CCollision::GetInstance() {
	if (__instance == NULL) __instance = new CCollision();
	return __instance;
}

void CCollision::AddCollisionBox(LPCollisionBox box)
{
	//collisionBoxes.push_back(box);
	collisionBoxes[box->GetId()] = box;
}

void CCollision::GetCollisionBoxes(int64_t exceptionId, std::list<LPCollisionBox> &outputList)
{
	outputList.clear();

	std::list<int64_t>::iterator it;
	//loop through active CBs
	for (it = activeCollisionBoxes.begin(); it != activeCollisionBoxes.end(); it++)
	{
		int64_t id = *it;
		if (id != exceptionId)
			outputList.push_back(this->GetCollisionBox(id));
	}
}

LPCollisionBox CCollision::GetCollisionBox(int64_t id)
{
	return collisionBoxes[id];
}

void CCollision::ResetActiveCollisionBoxes()
{
	activeCollisionBoxes.erase(
		activeCollisionBoxes.begin(),
		activeCollisionBoxes.end()
	);
}

void CCollision::AddActiveCollisionBoxes(int64_t lCB)
{
	activeCollisionBoxes.push_back(lCB);
}

void CCollision::AddActiveCollisionBoxes(std::list<int64_t> lCBs)
{
	activeCollisionBoxes.insert(activeCollisionBoxes.end(), lCBs.begin(), lCBs.end());
}

void SweptAABB(
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
		exit_x = static_right - move_left;
	}
	else
	{
		entry_x = static_right - move_left;
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
		//entry_time_x = -std::numeric_limits<float>::infinity();
		//exit_time_x = std::numeric_limits<float>::infinity();
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
		//entry_time_y = -std::numeric_limits<float>::infinity();
		//exit_time_y = std::numeric_limits<float>::infinity();
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
		entry_time_x < 0.0f && entry_time_y < 0.0f ||
		entry_time_x > 1.0f || entry_time_y > 1.0f)
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
		collide_time = entry_time;
	}
}

void GetSweptBroadphaseBox(
	float move_left, float move_top, float move_right, float move_bottom, 
	float move_velocity_x, float move_velocity_y, 
	float& target_left, float& target_top, float& target_right, float& target_bottom)
{
	if (move_velocity_x > 0)
	{
		target_left = move_left;
		target_right = move_right + move_velocity_x;
	}
	else
	{
		target_left = move_left + move_velocity_x;
		target_right = move_right;
	}

	if (move_velocity_y > 0)
	{
		target_top = move_top;
		target_bottom = move_bottom + move_velocity_y;
	}
	else
	{
		target_top = move_top + move_velocity_y;
		target_bottom = move_bottom;
	}
}

//return true is there is collision between to rectangle
bool AABBCheck(
	float left_1, float top_1, float right_1, float bottom_1, 
	float left_2, float top_2, float right_2, float bottom_2)
{
	return !(
		right_1 <= left_2 || 
		right_2 <= left_1 ||
		bottom_1 <= top_2 || 
		bottom_2 <= top_1);
}

void Deflect(
	float old_x, float old_y, 
	float& new_x, float& new_y, 
	float velocity_x, float velocity_y, 
	float collide_time, 
	float normal_x, float normal_y)
{
	//we sign new position = old position
	//then change these new position
	//the ideal is that we calculate the new position while keeping the old one
	new_x = old_x;
	new_y = old_y;

	new_x += velocity_x * collide_time;
	new_y += velocity_y * collide_time;

	float remaining_time = 1 - collide_time;

	velocity_x *= remaining_time;
	velocity_y *= remaining_time;

	if (abs(normal_x) > 0.0001f)
		velocity_x = -velocity_x;

	if (abs(normal_y) > 0.0001f)
		velocity_y = -velocity_y;

	//update position
	new_x += velocity_x;
	new_y += velocity_y;
}

void Push(
	float old_x, float old_y, 
	float& new_x, float& new_y, 
	float velocity_x, float velocity_y, 
	float collide_time, 
	float normal_x, float normal_y)
{
}

void Slide(
	float old_x, float old_y, 
	float& new_x, float& new_y, 
	float velocity_x, float velocity_y, 
	float collide_time, 
	float normal_x, float normal_y)
{
	//we sign new position = old position
	//then change these new position
	//the ideal is that we calculate the new position while keeping the old one
	new_x = old_x;
	new_y = old_y;

	new_x += velocity_x * collide_time;
	new_y += velocity_y * collide_time;

	float remaining_time = 1 - collide_time;

	//beware v_x * normal_y NOT v_x * normal_x
	float dotprod = (velocity_x * normal_y + velocity_y * normal_x) * remaining_time;

	velocity_x = dotprod * normal_y;
	velocity_y = dotprod * normal_x;

	//update position
	new_x += velocity_x;
	new_y += velocity_y;
}

