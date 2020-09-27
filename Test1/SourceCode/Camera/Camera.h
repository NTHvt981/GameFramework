#pragma once

#include "..\Vector\Vector.h"
#include "..\Constraints.h"

class CCamera
{
private:
	Vector position = Vector(0, 0);
	float width;
	float height;
	D3DXMATRIX matrix;

	static CCamera* __activeInstance;
public:
	static CCamera* GetInstance();
	static void SetInstance(CCamera &camera);

	CCamera(float w, float h);

	void SetMatrix();
	void Transform(float x, float y, D3DXVECTOR3 &new_pos);

	void Follow(float x, float y);
	void Follow(Vector pos);

	Vector GetPosition();

	float GetScale();
};

