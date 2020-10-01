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

CCamera::CCamera(float w, float h)
{
    width = w;
    height = h;
}

void CCamera::SetMatrix()
{
    D3DXMatrixIdentity(&matrix);

    matrix._22 = -1.0f;
    matrix._41 = -position.x;
    matrix._42 = position.y;
}

void CCamera::Transform(float x, float y, D3DXVECTOR3& new_pos)
{
    D3DXVECTOR3 old_pos(x, y, 0);
    D3DXVECTOR4 transform_vector_4;
    D3DXVec3Transform(&transform_vector_4, &old_pos, &matrix);

    new_pos.x = transform_vector_4.x;
    new_pos.y = transform_vector_4.y;
}

void CCamera::Follow(float x, float y)
{
    position.x = x - width / 2;
    position.y = y + height / 2;
}

void CCamera::Follow(Vector pos)
{
    Follow(pos.x, pos.y);
}

Vector CCamera::GetPosition()
{
    return position;
}

Vector CCamera::GetScale()
{
    return scale;
}

void CCamera::SetScale(float x, float y)
{
    scale.x = x;
    scale.y = y;
}

//float CCamera::GetScale()
//{
//    return scale;
//}
