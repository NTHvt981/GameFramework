#include "GameObject.h"


void CGameObject::Update(DWORD dt)
{
}

void CGameObject::Render()
{
}

GOTYPES CGameObject::GetType()
{
    return type;
}

void CGameObject::SetType(GOTYPES _type)
{
    type = _type;
}
