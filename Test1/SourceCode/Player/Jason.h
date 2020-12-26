#pragma once

#include "Player.h"
#include "../Constraints.h"
#include "../Unit/Animation.h"
#include "../PlayerBullets/JasonBullet.h"

#define JASON_CRAWL 0
#define JASON_WALK 1
#define JASON_CLIMB 2

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define MOTION 0
#define STILL 1

#define JASON_WALK_SPEED 0.75
#define JASON_CRAWL_SPEED 0.25
#define JASON_CLIMB_SPEED 0.5

class CJason :
    public CPlayer
{
private:
    LPAnimation animation;
    LPAnimation walkLeftAnimation;
    LPAnimation walkRightAnimation;
    LPAnimation crawlLeftAnimation;
    LPAnimation crawlRightAnimation;

    bool showAnimation = true;

    int state;
    int facing;
    int pace;

    float walkSpeed = 0.75;
    float crawlSpeed = 0.25;
    float climbSpeed = 0.5;

    Vector* posToDraw;
    Vector posClimbSpr = Vector(0, 0);
    Vector posWalkSpr = Vector(0, 0);
    Vector posCrawlSpr = Vector(-4, 8);

    Vector shootLeftWalkPivot = Vector(0, 0);
    Vector shootRightWalkPivot = Vector(0, 0);
    Vector shootLeftCrawlPivot = Vector(0, 4);
    Vector shootRightCrawlPivot = Vector(0, 4);

protected:
    void ApplyState(DWORD dt);
    void HandleSwitchToSophia();

public:
    void SetFacing(int _facing);

public:
    CJason(int _state = JASON_WALK, int _facing = RIGHT, int _pace = STILL);
    void Update(DWORD dt);
    void Render();

private:
    void onWalk(DWORD dt);
    void onCrawl(DWORD dt);
    void onClimb(DWORD dt);

protected:
    void SetHealthAnimation(DWORD dt);

    void Shoot();

private:
    static CJason* __instance;
public:
    static CJason* GetInstance();
};

