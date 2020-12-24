#include "Camera.h"

CCamera* CCamera::__activeInstance = NULL;

CCamera* CCamera::GetInstance()
{
    return __activeInstance;
}

void CCamera::SetInstance(CCamera& camera)
{
    __activeInstance = &camera;
}

CCamera::CCamera(float w, float h, float s)
{
   this->width = w / s;
   this->height = h / s;
   this->scale = s;

   //width - 320, height - 240
   innerBound.left = width / 3;
   innerBound.top = height / 3;

   innerBound.right = width - innerBound.left;
   innerBound.bottom = height - innerBound.top;
}

void CCamera::SetMatrix()
{
    D3DXMatrixIdentity(&matrix);

    //matrix._22 = -1.0f;
    //matrix._41 = -position.x;

    matrix._22 = 1.0f;
    matrix._41 = position.x;
    matrix._42 = position.y;

    matrix = matrix * scale;
}

void CCamera::Transform(float x, float y, D3DXVECTOR3& new_pos)
{
    D3DXVECTOR3 old_pos(x, y, 0);
    D3DXVECTOR4 transform_vector_4;
    //D3DXVec3Transform(&transform_vector_4, &old_pos, &matrix);

    //new_pos.x = transform_vector_4.x;
    //new_pos.y = transform_vector_4.y;

    new_pos.x = x - position.x;
    new_pos.y = y - position.y;
}

void CCamera::Follow(float x, float y)
{
    //position.x = x - width/2;
    //position.y = y - height/2;
    
    float _x = x - position.x;
    float _y = y - position.y;

    //float l_x = innerBound.left - _x;
    //float t_y = innerBound.top - _y;

    float x_l = _x - innerBound.left;
    float y_t = _y - innerBound.top;
    float x_r = _x - innerBound.right;
    float y_b = _y - innerBound.bottom;

    float move_x = 0;
    float move_y = 0;

    if (x_l < 0)
        move_x = x_l;
    if (x_r > 0)
        move_x = x_r;
    if (y_t < 0)
        move_y = y_t;
    if (y_b > 0)
        move_y = y_b;

    position.x += move_x;
    position.y += move_y;

    if (position.x < outerBound.left)
        position.x = outerBound.left;
    if (position.x + width > outerBound.right)
        position.x = outerBound.right - width;

    if (position.y < outerBound.top)
        position.y = outerBound.top;
    if (position.y + height > outerBound.bottom)
        position.y = outerBound.bottom - height;

    float l, t, r, b;
    GetLTRB(l, t, r, b);
}

void CCamera::Follow(Vector pos)
{
    Follow(pos.x, pos.y);
}

void CCamera::FollowWithoutPlayer(float x, float y)
{
    position.x = x;
    position.y = y;
}

void CCamera::Move(float vx, float vy)
{
    position.x += vx;
    position.y += vy;
}

Vector CCamera::GetPosition()
{
    return position;
}

void CCamera::GetLTRB(float& l, float& t, float& r, float& b)
{
    l = position.x;
    t = position.y;
    r = position.x + width;
    b = position.y + height;
}

float CCamera::GetScale()
{
    return scale;
}

void CCamera::SetOuterBound(float l, float t, float r, float b) 
{
    outerBound.left = l;
    outerBound.top = t;
    outerBound.right = r;
    outerBound.bottom = b;
}

//float CCamera::GetScale()
//{
//    return scale;
//}
