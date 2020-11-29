#include "Jason.h"

void CJason::SetState(DWORD dt)
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

void CJason::GetState(DWORD dt)
{
}

CJason::CJason() : CPlayer()
{
	gravity = 0.2;
	jumpSpeed = 3;

	collisionBox = new CDynamicBox(
		this,
		0, 0,
		8, 16
	);
	collisionBox->SetSolid(false);

	CSpriteLibrary* lib = CSpriteLibrary::GetInstance();

	walkLeftAnimation = new CAnimation(1, 100);
	int ids1[] = {
		ID_JASON_WALK_LEFT_1,
		ID_JASON_WALK_LEFT_2,
		ID_JASON_WALK_LEFT_3,
		ID_JASON_WALK_LEFT_4,
	};
	walkLeftAnimation->Add(ids1, 4);

	walkRightAnimation = new CAnimation(1, 100);
	int ids2[] = {
		ID_JASON_WALK_RIGHT_1,
		ID_JASON_WALK_RIGHT_2,
		ID_JASON_WALK_RIGHT_3,
		ID_JASON_WALK_RIGHT_4,
	};
	walkRightAnimation->Add(ids2, 4);

	crawlLeftAnimation = new CAnimation(1, 200);
	int ids3[] = {
		ID_JASON_CRAWL_LEFT_1,
		ID_JASON_CRAWL_LEFT_2
	};
	crawlLeftAnimation->Add(ids3, 2);

	crawlRightAnimation = new CAnimation(1, 200);
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

	SetState(dt);

	CPlayerHealth* healthSystem = CPlayerHealth::GetInstance();
	if (IsCollidedWith(GOTYPES::Enemy) || IsCollidedWith(GOTYPES::EnemyBullet))
		healthSystem->ReduceHealth(GOTYPES::Jason);

	if (healthSystem->GetHealthState() == INVULNERABLE)
		SetHealthAnimation(dt);

	if (pace == STILL)
	{
		animation->SetCurrentFrame(0);
		animation->SetMode(ANIMATION_PAUSE);
	}
	else if (pace == MOTION)
		animation->SetMode(ANIMATION_NORMAL);
}

void CJason::Render()
{
	//animation->Render(position + posToDraw);
	animation->Render(Vector(
		position.x + posToDraw->x,
		position.y + posToDraw->y
	));
}

void CJason::onWalk(DWORD dt)
{
	CInput* input = CInput::GetInstance();
	velocity.x = dt * walkSpeed * (
		input->IsKeyDown(DIK_D) - input->IsKeyDown(DIK_A)
	);

	if (onGround)
		if (input->IsKeyDown(DIK_K))
		{
			velocity.y = -jumpSpeed;
		}

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
	velocity.x = dt * crawlSpeed * (
		input->IsKeyDown(DIK_D) - input->IsKeyDown(DIK_A)
		);

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

	if (input->IsKeyPressed(DIK_W))
		state = JASON_WALK;

	onGround = true;
}

void CJason::onClimb(DWORD dt)
{
	CInput* input = CInput::GetInstance();
	velocity.x = dt * climbSpeed * (
		input->IsKeyDown(DIK_D) - input->IsKeyDown(DIK_A)
		);
	velocity.y = dt * climbSpeed * (
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
	if (velocity.y == 0 && input->IsKeyDown(DIK_S))
		state = JASON_WALK;

	onGround = false;
}

void CJason::SetHealthAnimation(DWORD dt)
{
}

void CJason::Shoot(int aim_direction)
{
}
