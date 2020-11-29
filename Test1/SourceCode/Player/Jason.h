#pragma once

#include "Player.h"
#include "../Constraints.h"
#include "../Unit/Animation.h"

#define JASON_CRAWL 0
#define JASON_WALK 1
#define JASON_CLIMB 2

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define MOTION 0
#define STILL 1

class CJason :
    public CPlayer
{
private:
    LPAnimation animation;
    LPAnimation walkLeftAnimation;
    LPAnimation walkRightAnimation;
    LPAnimation crawlLeftAnimation;
    LPAnimation crawlRightAnimation;

    int state = JASON_WALK;
    int facing = RIGHT;
    int pace = STILL;

    float walkSpeed = 0.75;
    float crawlSpeed = 0.25;
    float climbSpeed = 0.5;

    Vector* posToDraw;
    Vector posClimbSpr = Vector(0, 0);
    Vector posWalkSpr = Vector(0, 0);
    Vector posCrawlSpr = Vector(-8, 8);

protected:
    void SetState(DWORD dt);
    void GetState(DWORD dt);

public:
    CJason();
    void Update(DWORD dt);
    void Render();

private:
    void onWalk(DWORD dt);
    void onCrawl(DWORD dt);
    void onClimb(DWORD dt);

protected:
    void SetHealthAnimation(DWORD dt);

    void Shoot(int aim_direction);
};

