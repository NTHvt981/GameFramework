#include "GameObject.h"


CGameObject::CGameObject()
{
}

void CGameObject::Disable()
{
    enable = false;
    visible = false;
}

void CGameObject::Enable()
{
    enable = true;
    visible = true;
}

void CGameObject::Pause()
{
    enable = false;
}

void CGameObject::Unpause()
{
    enable = true;
}

void CGameObject::Update(DWORD dt)
{
}

void CGameObject::Render()
{
}

GOTYPES CGameObject::GetType()
{
    return Type;
}

void CGameObject::SetType(GOTYPES _type)
{
    Type = _type;
}
