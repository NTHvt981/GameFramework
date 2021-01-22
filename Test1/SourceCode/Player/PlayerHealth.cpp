#include "PlayerHealth.h"

CPlayerHealth* CPlayerHealth::__instance = NULL;

CPlayerHealth* CPlayerHealth::GetInstance()
{
    if (__instance == NULL)
        __instance = new CPlayerHealth();

    return __instance;
}

CPlayerHealth::CPlayerHealth()
{
    invulnerableTimer = new CTimer(100);
    sophiaHealth = sophiaMaxHealth;
    jasonHealth = jasonMaxHealth;

    sprSophiaHealthBar = CSpriteLibrary::GetInstance()->Get(ID_SOPHIA_HEALTH_BAR);
    sprJasonHealthBar = CSpriteLibrary::GetInstance()->Get(ID_JASON_HEALTH_BAR);
    sprTextHov = CSpriteLibrary::GetInstance()->Get(ID_TEXT_HOV);
    sprTextPow = CSpriteLibrary::GetInstance()->Get(ID_TEXT_POW);
}

void CPlayerHealth::turnOnInvulnerability()
{
    healthState = INVULNERABLE;
    invulnerableTimer->Start();

    DebugOut(L"[INFO] turn on invulnerability\n");
}

void CPlayerHealth::turnOffInvulnerability()
{
    healthState = VULNERABLE;

    DebugOut(L"[INFO] turn off invulnerability\n");
}

void CPlayerHealth::Restart()
{
    this->sophiaHealth = this->sophiaMaxHealth;
    this->jasonHealth = this->jasonMaxHealth;

    gameOver = false;
}

void CPlayerHealth::ReduceSophiaHealth(int damage)
{
    sophiaHealth = max(sophiaHealth - damage, 0);
    if (sophiaHealth == 0) gameOver = true;
    turnOnInvulnerability();

    DebugOut(L"[INFO] reduce sophia health by 1\n");
    DebugOut(L"[INFO] sophia health now is %d\n", sophiaHealth);
}

void CPlayerHealth::IncreaseSophiaHealth(int heal_points)
{
    sophiaHealth = min(sophiaHealth + heal_points, sophiaMaxHealth);

    DebugOut(L"[INFO] increase sophia health by 1\n");
    DebugOut(L"[INFO] sophia health now is %d\n", sophiaHealth);
}

void CPlayerHealth::ReduceJasonHealth(int damage)
{
    jasonHealth = max(jasonHealth - damage, 0);
    if (jasonHealth == 0) gameOver = true;
    turnOnInvulnerability();

    DebugOut(L"[INFO] reduce jason health by 1\n");
    DebugOut(L"[INFO] jason health now is %d\n", jasonHealth);
}

void CPlayerHealth::IncreaseJasonHealth(int heal_points)
{
    jasonHealth = min(jasonHealth + heal_points, jasonMaxHealth);

    DebugOut(L"[INFO] increase jason health by 1\n");
    DebugOut(L"[INFO] jason health now is %d\n", jasonHealth);
}

void CPlayerHealth::ReduceHealth(GOTYPES Type, int damage)
{
    if (healthState == INVULNERABLE) return;

    if (Type == GOTYPES::Jason)
        ReduceJasonHealth(damage);
    else if (Type == GOTYPES::Sophia)
        ReduceSophiaHealth(damage);

    CSoundLibrary::GetInstance()->PlayPlayerHurtSound();
}

void CPlayerHealth::ReduceHealth(int damage)
{
    if (playerMode == SOPHIA)
        ReduceSophiaHealth(damage);
    else if (playerMode == JASON)
        ReduceJasonHealth(damage);

    CSoundLibrary::GetInstance()->PlayPlayerHurtSound();
}

void CPlayerHealth::IncreaseHealth(GOTYPES Type, int heal_points)
{
    if (Type == GOTYPES::Jason)
        IncreaseJasonHealth(heal_points);
    else if (Type == GOTYPES::Sophia)
        IncreaseSophiaHealth(heal_points);
}

void CPlayerHealth::IncreaseHealth(int heal_points)
{
    if (playerMode == SOPHIA)
        IncreaseSophiaHealth(heal_points);
    else if (playerMode == JASON)
        IncreaseJasonHealth(heal_points);
}

void CPlayerHealth::SetPlayerMode(int _mode)
{
    playerMode = _mode;
}

int CPlayerHealth::GetHealthState()
{
    return healthState;
}

bool CPlayerHealth::IsGameOver()
{
    return gameOver;
}

void CPlayerHealth::Update(DWORD dt)
{
    SetCheat(dt);
    if (cheat) return;

    invulnerableTimer->Update(dt);
    if (invulnerableTimer->JustFinish()) turnOffInvulnerability();
}

void CPlayerHealth::Render()
{
    sprTextPow->DrawWithFixedPosition(textPowPivot.x, textPowPivot.y);
    sprTextHov->DrawWithFixedPosition(textHovPivot.x, textHovPivot.y);

    int count = 0;
    int healthBarHeight, healthBarWidth;
    LPSprite healthBarToDraw = sprSophiaHealthBar;

    if (playerMode == SOPHIA)
    {
        count = sophiaHealth;
        healthBarToDraw = sprSophiaHealthBar;
    }
    else
    {
        count = jasonHealth;
        healthBarToDraw = sprJasonHealthBar;
    }

    healthBarToDraw->GetSize(healthBarWidth, healthBarHeight);

    for (int i = 0; i < count; i++)
    {
        healthBarToDraw->DrawWithFixedPosition(
            textHealthBarPivot.x,
            textHealthBarPivot.y - i * ( healthBarHeight + 2 )
        );
    }
}

void CPlayerHealth::SetCheat(DWORD dt)
{
    CInput* input = CInput::GetInstance();
    if (input->IsKeyPressed(DIK_E))
    {
        if (cheat)
        {
            cheat = false;
            healthState = VULNERABLE;
            DebugOut(L"[INFO] CHEAT MODE OFF\n");
        }
        else
        {
            cheat = true;
            healthState = INVULNERABLE;
            DebugOut(L"[INFO] CHEAT MODE ON\n");
        }
    }
}
