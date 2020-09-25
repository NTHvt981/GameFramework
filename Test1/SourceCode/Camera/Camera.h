#pragma once

#include "..\Vector\Vector.h"
#include "..\Constraints.h"

class CCamera
{
private:
	Vector position = Vector(0, 0);

	static CCamera* __activeInstance;
public:
	static CCamera* GetInstance();
	static void SetInstance(CCamera &camera);

	CCamera(Vector v);
	CCamera(float x, float y);

	void SetPosition(Vector v);
	void SetPosition(float x, float y);
	Vector GetPosition();
};

