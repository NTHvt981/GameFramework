#pragma once

#include <list>
#include <map>
#include "Constraints.h"
#include "CollisionBox.h"



//Class that handle basic function of calculating collision
class CCollision
{
private:
	static CCollision* __instance;

	//contain all collision box
	std::map<int64_t, LPCollisionBox> collisionBoxes;
	//contain collision box get call for collision
	std::list<int64_t> activeCollisionBoxes;

public:
	static CCollision* GetInstance();

	void AddCollisionBox(LPCollisionBox box);
	void GetCollisionBoxes(int64_t exceptionId, std::list<LPCollisionBox>& outputList);
	LPCollisionBox GetCollisionBox(int64_t id);

	//set active std::list empty
	void ResetActiveCollisionBoxes();
	void AddActiveCollisionBoxes(int64_t lCB);
	void AddActiveCollisionBoxes(std::list<int64_t> lCBs);
};

//vital functions for game object to use
void SweptAABB(
	float move_left, float move_top, float move_right, float move_bottom,
	float move_velocity_x, float move_velocity_y,
	float static_left, float static_top, float static_right, float static_bottom,
	float& collide_time,
	float& normal_x, float& normal_y	//std::vector x and y vuong goc voi be mat xay ra va cham
);
void GetSweptBroadphaseBox(
	float move_left, float move_top, float move_right, float move_bottom,
	float move_velocity_x,
	float move_velocity_y,
	float& target_left, float& target_top, float& target_right, float& target_bottom
);
bool AABBCheck(
	//left -> top -> right -> bottom
	float left_1, float top_1, float right_1, float bottom_1,
	float left_2, float top_2, float right_2, float bottom_2);
void Deflect(
	float old_x, float old_y,
	float& new_x, float& new_y,
	float velocity_x, float velocity_y,
	float collide_time,
	float normal_x, float normal_y
);
void Push(
	float old_x, float old_y,
	float& new_x, float& new_y,
	float velocity_x, float velocity_y,
	float collide_time,
	float normal_x, float normal_y
);
void Slide(
	float old_x, float old_y,
	float& new_x, float& new_y,
	float velocity_x, float velocity_y,
	float collide_time,
	float normal_x, float normal_y
);