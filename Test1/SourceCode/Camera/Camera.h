#pragma once

#include "..\Vector\Vector.h"
#include "..\Constraints.h"
#include "..\Vector\Box.h"

class CCamera
{
private:
	Vector position = Vector(0, 200);
	Vector goalPosition;
	float width;
	float height;
	float scale;
	D3DXMATRIX matrix;

	/*	y
	x	o---------------------------o
		|				 |			|
		|	o-----------o|//inner.b	|
		|	|innerBound	||			|	outerBound
		|	o-----------ov			|
		|<-------------->			|
		|	//inner.r				|
		o---------------------------o
	*/

	//limit of camera position to the game world
	Box<float> outerBound;
	//limit of player position relative to camera rect
	Box<float> innerBound;

	static CCamera* __activeInstance;
public:
	static CCamera* GetInstance();
	static void SetInstance(CCamera &camera);

	static D3DXMATRIX MirrorHorizontal(D3DXVECTOR3& vector);

	CCamera(float w, float h, float s=1);

	void SetMatrix();
	void Transform(float x, float y, D3DXVECTOR3 &new_pos);

	//these function should be called in game class rather than player class
	void Follow(float x, float y);
	void Follow(Vector pos);

	void FollowWithTransition(float x, float y);
	void FollowWithTransition(Vector pos);

	void FollowWithoutPlayer(float x, float y);

	void Move(float vx, float vy);

	Vector GetPosition();
	void GetLTRB(float& l, float& t, float& r, float& b);

	float GetScale();

	void SetOuterBound(float l, float t, float r, float b);
	void GetOuterBound(float &l, float &t, float &r, float &b);
};

