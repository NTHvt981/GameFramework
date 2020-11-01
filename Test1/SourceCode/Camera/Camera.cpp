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
}

void CCamera::SetMatrix()
{
    D3DXMatrixIdentity(&matrix);

    matrix._22 = -1.0f;
    matrix._41 = -position.x;
    matrix._42 = position.y;

    matrix = matrix * scale;
}

void CCamera::Transform(float x, float y, D3DXVECTOR3& new_pos)
{
    D3DXVECTOR3 old_pos(x, y, 0);
    D3DXVECTOR4 transform_vector_4;
    D3DXVec3Transform(&transform_vector_4, &old_pos, &matrix);

    new_pos.x = transform_vector_4.x;
    new_pos.y = transform_vector_4.y;
}

void CCamera::Transform(float x, float y, float origin_x, float origin_y, D3DXMATRIX& _matrix)
{
    D3DXVECTOR2 center = D3DXVECTOR2(origin_x, origin_y);
    D3DXVECTOR2 translate = D3DXVECTOR2(x, y);
    D3DXVECTOR2 scaling = D3DXVECTOR2(1, 1);
    float angle = 0;

    SetRenderData(center, translate, scaling);

    D3DXMatrixTransformation2D(
        &matrix,
        NULL,
        0.0f,
        &scaling,
        &center,
        angle,
        &translate
    );
}

void CCamera::SetRenderData(D3DXVECTOR2& center, D3DXVECTOR2& translate, D3DXVECTOR2& scaling)
{
    D3DXMATRIX mt;
    D3DXMatrixIdentity(&mt);
    mt._22 = -1;
    matrix._41 = -position.x;
    matrix._42 = position.y;
    D3DXVECTOR4 curTranslate;
    D3DXVECTOR4 curCenter;

    D3DXVec2Transform(&curCenter, &D3DXVECTOR2(center.x, center.y), &mt);

    D3DXVec2Transform(&curTranslate, &D3DXVECTOR2(translate.x, translate.y), &mt);

    center.x = curCenter.x;
    center.y = curCenter.y;
    translate.x = curTranslate.x;
    translate.y = curTranslate.y;
}

void CCamera::Follow(float x, float y)
{
    position.x = x - width / 2;
    position.y = y + height / 2;

    float l, t, r, b;
    GetLTRB(l, t, r, b);

    //if (position.y < height/2)
    //    position.y = height;

    //if (position.x < 0)
    //    position.x = 0;
}

void CCamera::Follow(Vector pos)
{
    Follow(pos.x, pos.y);
}

Vector CCamera::GetPosition()
{
    return position;
}

void CCamera::GetLTRB(float& l, float& t, float& r, float& b)
{
    l = position.x;
    t = position.y - height;
    r = position.x + width;
    b = position.y;
}

float CCamera::GetScale()
{
    return scale;
}

//float CCamera::GetScale()
//{
//    return scale;
//}
