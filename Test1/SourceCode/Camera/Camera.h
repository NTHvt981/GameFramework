#pragma once

#include "..\Vector\Vector.h"
#include "..\Constraints.h"

class CCamera
{
private:
	Vector position = Vector(0, 0);
	float width;
	float height;
	float scale;
	D3DXMATRIX matrix;

	static CCamera* __activeInstance;
public:
	static CCamera* GetInstance();
	static void SetInstance(CCamera &camera);

	static D3DXMATRIX MirrorHorizontal(D3DXVECTOR3& vector);

	CCamera(float w, float h, float s=1);

	void SetMatrix();
	void Transform(float x, float y, D3DXVECTOR3 &new_pos);
	void Transform(float x, float y, float origin_x, float origin_y, 
		D3DXMATRIX& _matrix);
	void SetRenderData(D3DXVECTOR2& center, D3DXVECTOR2& translate, D3DXVECTOR2& scaling);

	void Follow(float x, float y);
	void Follow(Vector pos);

	Vector GetPosition();
	void GetLTRB(float& l, float& t, float& r, float& b);

	float GetScale();
};

