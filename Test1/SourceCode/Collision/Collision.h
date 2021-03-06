#pragma once

#include <list>
#include <map>
#include "..\Constraints.h"
#include "CollisionBox.h"

using namespace std;

//Class that handle basic function of calculating collision
class CCollision
{
private:
	static CCollision* __instance;

	//contain all collision box
	map<int, LPCollisionBox> collisionBoxes;
	//contain collision box get call for collision
	list<int> activeCollisionBoxes;

public:
	static CCollision* GetInstance();

	void AddCollisionBox(LPCollisionBox box);
	void GetCollisionBoxes(int exceptionId, list<LPCollisionBox>& outputList);
	LPCollisionBox GetCollisionBox(int id);

	//set active list empty
	void ResetActiveCollisionBoxes();
	void AddActiveCollisionBoxes(int lCB);
	void AddActiveCollisionBoxes(list<int> lCBs);
};

//vital functions for game object to use
void SweptAABB(
	float move_left, float move_top, float move_right, float move_bottom,
	float move_velocity_x, float move_velocity_y,
	float static_left, float static_top, float static_right, float static_bottom,
	float& collide_time,
	float& normal_x, float& normal_y	//vector x and y vuong goc voi be mat xay ra va cham
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