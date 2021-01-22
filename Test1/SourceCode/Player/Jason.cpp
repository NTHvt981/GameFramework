#include "Jason.h"

CJason* CJason::__instance = NULL;

void CJason::ApplyState(DWORD dt)
{
	switch (state)
	{
	case JASON_WALK:
		onWalk(dt);
		break;
	case JASON_CRAWL:
		onCrawl(dt);
		break;
	case JASON_CLIMB:
		onClimb(dt);
		break;
	default:
		break;
	}
}

void CJason::HandleSwitchToSophia()
{
	if (IsCollidedWith(GOTYPES::FakeSophia))
	{
		if (CInput::GetInstance()->IsKeyPressed(DIK_L))
		{
			LPSceneRequest swSophiaReq = new CSceneRequest(SCENE_REQUEST_TYPES::SwitchToSophia);
			CSceneRequest::AddRequest(swSophiaReq);
		}
	}
}

void CJason::SetFacing(int _facing)
{
	facing = _facing;
}

CJason::CJason(int _state, int _facing, int _pace) : CPlayer()
{
	gravity = 0.2;
	jumpSpeed = 3;

	state = _state;
	facing = _facing;
	pace = _pace;

	collisionBox = new CDynamicBox(
		this,
		0, 0,
		8, 16
	);
	collisionBox->SetSolid(false);

	CSpriteLibrary* lib = CSpriteLibrary::GetInstance();

	walkLeftAnimation = new CAnimation(100);
	int ids1[] = {
		ID_JASON_WALK_LEFT_1,
		ID_JASON_WALK_LEFT_2,
		ID_JASON_WALK_LEFT_3,
		ID_JASON_WALK_LEFT_4,
	};
	walkLeftAnimation->Add(ids1, 4);

	walkRightAnimation = new CAnimation(100);
	int ids2[] = {
		ID_JASON_WALK_RIGHT_1,
		ID_JASON_WALK_RIGHT_2,
		ID_JASON_WALK_RIGHT_3,
		ID_JASON_WALK_RIGHT_4,
	};
	walkRightAnimation->Add(ids2, 4);

	crawlLeftAnimation = new CAnimation(200);
	int ids3[] = {
		ID_JASON_CRAWL_LEFT_1,
		ID_JASON_CRAWL_LEFT_2
	};
	crawlLeftAnimation->Add(ids3, 2);

	crawlRightAnimation = new CAnimation(200);
	int ids4[] = {
		ID_JASON_CRAWL_RIGHT_1,
		ID_JASON_CRAWL_RIGHT_2
	};
	crawlRightAnimation->Add(ids4, 2);

	animation = walkRightAnimation;
}

void CJason::Update(DWORD dt)
{
	CPlayer::Update(dt);

	CInput* input = CInput::GetInstance();

	keyUp = input->IsKeyDown(DIK_W);
	keyLeft = input->IsKeyDown(DIK_A);
	keyRight = input->IsKeyDown(DIK_D);
	keyDown = input->IsKeyDown(DIK_S);

	keyJump = input->IsKeyDown(DIK_K);
	keyShoot = input->IsKeyDown(DIK_J);
	keySwitchPlayer = input->IsKeyPressed(DIK_L);

	ApplyState(dt);

	CPlayerHealth* healthSystem = CPlayerHealth::GetInstance();
	if (IsCollidedWith(GOTYPES::Enemy) || IsCollidedWith(GOTYPES::EnemyBullet))
		healthSystem->ReduceHealth(GOTYPES::Jason);

	SetHealthAnimation(dt);

	if (pace == STILL)
	{
		animation->SetCurrentFrame(0);
		animation->SetMode(ANIMATION_PAUSE);
	}
	else if (pace == MOTION)
		animation->SetMode(ANIMATION_NORMAL);

	HandleShooting(dt);
	HandleSwitchToSophia();
}

void CJason::Render()
{
	if (!visible) return;

	//animation->Render(position + posToDraw);
	if (showAnimation)
		animation->Render(Vector(
			position.x + posToDraw->x,
			position.y + posToDraw->y
		));
	collisionBox->Render();
}

void CJason::onWalk(DWORD dt)
{
	CInput* input = CInput::GetInstance();
	//velocity.x = walkSpeed * (
	//	input->IsKeyDown(DIK_D) - input->IsKeyDown(DIK_A)
	//);
	HandleMove(dt, JASON_WALK_SPEED, JASON_MOVE_FRICTION);
	HandleJump(dt);

	//Set state for animation
	if (velocity.x > 0)
	{
		facing = RIGHT;
		pace = MOTION;
	}
	else if (velocity.x < 0)
	{
		facing = LEFT;
		pace = MOTION;
	}
	else
		pace = STILL;

	//Set animation
	if (facing == RIGHT)
		animation = walkRightAnimation;
	else if (facing == LEFT)
		animation = walkLeftAnimation;
	posToDraw = &posWalkSpr;

	old_velocity.Set(velocity.x, velocity.y);
	Move(dt);
	collisionBox->Update();

	/// <summary>
	/// Check Climbing section
	/// </summary>
	if (IsCollidedWith(GOTYPES::Ladder) && input->IsKeyDown(DIK_W))
		state = JASON_CLIMB;
	if (input->IsKeyDown(DIK_S))
		state = JASON_CRAWL;

	if (velocity.y < 0)
		onGround = false;
	else if (velocity.y == 0 && old_velocity.y > 0)
		onGround = true;
}

void CJason::onCrawl(DWORD dt)
{
	CInput* input = CInput::GetInstance();
	HandleMove(dt, JASON_CRAWL_SPEED, JASON_MOVE_FRICTION);

	if (velocity.x > 0)
	{
		facing = RIGHT;
		pace = MOTION;
	}
	else if (velocity.x < 0)
	{
		facing = LEFT;
		pace = MOTION;
	}
	else
		pace = STILL;

	//Set animation
	if (facing == RIGHT)
		animation = crawlRightAnimation;
	else if (facing == LEFT)
		animation = crawlLeftAnimation;
	posToDraw = &posCrawlSpr;

	old_velocity.Set(velocity.x, velocity.y);
	Move(dt);
	collisionBox->Update();

	if (keyUp)
		state = JASON_WALK;

	onGround = true;
}

void CJason::onClimb(DWORD dt)
{
	CInput* input = CInput::GetInstance();
	velocity.x = JASON_CLIMB_SPEED * (
		input->IsKeyDown(DIK_D) - input->IsKeyDown(DIK_A)
		);
	velocity.y = JASON_CLIMB_SPEED * (
		input->IsKeyDown(DIK_S) - input->IsKeyDown(DIK_W)
		);

	if (velocity.x > 0 || velocity.y > 0)
	{
		facing = RIGHT;
		pace = MOTION;
	}
	else if (velocity.x < 0 || velocity.y < 0)
	{
		facing = LEFT;
		pace = MOTION;
	}
	else
		pace = STILL;

	//Set animation (TODO add later)
	//if (facing == RIGHT)
	//	animation = cli;
	//else if (facing == LEFT)
	//	animation = crawlLeftAnimation;
	posToDraw = &posClimbSpr;

	old_velocity.Set(velocity.x, velocity.y);
	MoveWithoutGravity(dt);
	collisionBox->Update();
	
	/// <summary>
	/// Check Climbing section
	/// </summary>
	if (!IsCollidedWith(GOTYPES::Ladder))
		state = JASON_WALK;
	if (velocity.y == 0 && keyDown)
		state = JASON_WALK;

	onGround = false;
}

void CJason::HandleMove(DWORD dt, float maxSpeed, float friction)
{
	CInput* input = CInput::GetInstance();
	int moveKey = input->IsKeyDown(DIK_D) - input->IsKeyDown(DIK_A);

	if (moveKey != 0)
		velocity.x += friction * moveKey;
	else
	{
		if (velocity.x > 0)
			velocity.x = max(velocity.x - friction, 0);
		else if (velocity.x < 0)
			velocity.x = min(velocity.x + friction, 0);
	}

	if (velocity.x > maxSpeed)
		velocity.x = maxSpeed;
	else if (velocity.x < -maxSpeed)
		velocity.x = -maxSpeed;
}

void CJason::HandleJump(DWORD dt)
{
	CInput* input = CInput::GetInstance();
	bool keyJump = input->IsKeyDown(DIK_K);
	bool keyJumpRelease = input->IsKeyRelease(DIK_K);

	if (onGround && keyJump)
	{
		jumpCountUp += dt;
	}
	else if (onGround && keyJumpRelease)
	{
		if (jumpCountUp >= jumpWaitTime)
			velocity.y = -JASON_HIGH_JUMP_SPEED;
		else
			velocity.y = -JASON_LOW_JUMP_SPEED;
	}
	else
		jumpCountUp = 0;
}

void CJason::SetHealthAnimation(DWORD dt)
{
	CPlayerHealth* healthSystem = CPlayerHealth::GetInstance();

	if (healthSystem->GetHealthState() == INVULNERABLE)
	{
		healthAniCountTime += dt;
		if (healthAniCountTime >= healthAniWaitTime)
		{
			healthAniCountTime = 0;

			if (healthAniWhiteFlip)
			{
				healthAniWhiteFlip = false;
			}
			else
			{
				healthAniWhiteFlip = true;
			}
		}
	}
	else healthAniWhiteFlip = false;

	if (healthAniWhiteFlip)
	{
		showAnimation = false;
	}
	else
	{
		showAnimation = true;
	}
}

void CJason::Shoot()
{
	Vector* shoot_pivot = &shootRightWalkPivot;
	Vector direction = Vector(0, 0);

	if (facing == RIGHT && state == JASON_WALK)
	{
		shoot_pivot = &shootRightWalkPivot;
		direction = Vector(1, 0);
	}
	else if (facing == LEFT && state == JASON_WALK)
	{
		shoot_pivot = &shootLeftWalkPivot;
		direction = Vector(-1, 0);
	}
	else if (facing == RIGHT && state == JASON_CRAWL)
	{
		shoot_pivot = &shootRightCrawlPivot;
		direction = Vector(1, 0);
	}
	else if (facing == LEFT && state == JASON_CRAWL)
	{
		shoot_pivot = &shootLeftCrawlPivot;
		direction = Vector(-1, 0);
	}

	float x = (*shoot_pivot).x + GetCenter().x;
	float y = (*shoot_pivot).y + GetCenter().y;

	try
	{
		LPSceneRequest request = new CSceneRequest(SCENE_REQUEST_TYPES::CreateEntity);
		request->entity = new CJasonBullet(
			direction
		);
		request->x = x;
		request->y = y;

		CSceneRequest::AddRequest(request);
	}
	catch (const std::exception& ex)
	{
		DebugOut(L"[ERROR] create bullet %s \n", ex.what());
	}

	shootCountTime = 0;
	canShoot = false;

	CSoundLibrary::GetInstance()->PlayPlayerShootSound();
}

CJason* CJason::GetInstance()
{
	if (__instance == NULL)
		__instance = new CJason();

	return __instance;
}
