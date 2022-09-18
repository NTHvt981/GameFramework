#pragma once

#include "Player.h"
#include "Constraints.h"
#include "Animation.h"
#include "JasonTopDownBullet.h"

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define MOTION 0
#define STILL 1

#define JASON_TOPDOWN_FRAME_TIME 150

#define JASON_TOP_DOWN_MOVE_SPEED 1.5

class CJasonTopDown :
    public CPlayer
{
protected:
    float speed = 1.5;

    Vector* posToDraw;
    Vector posHorSpr = Vector(0, 0);
    Vector posVerSpr = Vector(2, 0);

    Vector leftShootPivot = Vector(-6, -6);
    Vector rightShootPivot = Vector(6, -6);
    Vector downShootPivot = Vector(-4, -2);
    Vector upShootPivot = Vector(4, -8);

private:
    LPAnimation animation;
    LPAnimation walkLeftAnimation;
    LPAnimation walkUpAnimation;
    LPAnimation walkRightAnimation;
    LPAnimation walkDownAnimation;

    bool showAnimation = true;

    int64_t facing;
    int64_t pace;

public:
    void SetFacing(int64_t _facing);

public:
    CJasonTopDown(int64_t _facing = RIGHT, int64_t _pace = STILL);
    void Update(DWORD dt);
    void Render();

protected:
    void SetHealthAnimation(DWORD dt);
    void GetSetAnimation(DWORD dt, int64_t _facing, int64_t _pace);

    void Shoot();

private:
    static CJasonTopDown* __instance;
public:
    static CJasonTopDown* GetInstance();

private:
    void HandleAreaTransitioning(DWORD dt);
};

