#include "Camera.h"

CCamera* CCamera::__activeInstance = NULL;

CCamera* CCamera::GetInstance()
{
    if (__activeInstance == NULL) 
        return NULL;
    return __activeInstance;
}

void CCamera::SetInstance(CCamera& camera)
{
    __activeInstance = &camera;
}

CCamera::CCamera(Vector v)
{
    position = v;
}

CCamera::CCamera(float x, float y)
{
    position.x = x;
    position.y = y;
}

void CCamera::SetPosition(Vector v)
{
    position = v;
}

void CCamera::SetPosition(float x, float y)
{
    position.x = x;
    position.y = y;
}

Vector CCamera::GetPosition()
{
    return position;
}
