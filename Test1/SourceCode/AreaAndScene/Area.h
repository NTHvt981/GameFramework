#pragma once
class CArea
{
public:
	float left;
	float top;
	float right;
	float bottom;

public:
	CArea(float l, float t, float r, float b);
	void GetLTRB(float &l, float& t, float& r, float& b);
};

