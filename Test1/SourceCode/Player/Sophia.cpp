#include "Sophia.h"

void CSophia::onLeft(DWORD dt)
{
	if (keyRight)
		nextState = ON_RIGHT;

	if (keyUp) face = FACE_UP_LEFT;
	else face = FACE_LEFT;

	headSprite = CSpriteLibrary::GetInstance()->Get(ID_SOPHIA_HEAD_LEFT);
	showCanon = true;
}

void CSophia::onRight(DWORD dt)
{
	if (keyLeft)
		nextState = ON_LEFT;

	if (keyUp) face = FACE_UP_RIGHT;
	else face = FACE_RIGHT;

	headSprite = CSpriteLibrary::GetInstance()->Get(ID_SOPHIA_HEAD_RIGHT);
	showCanon = true;
}

void CSophia::onLeftTurnRight(DWORD dt)
{
	if (headTurnRightAni->IsEnd())
		nextState = ON_RIGHT;

	headAni = headTurnRightAni;
	showCanon = false;
}

void CSophia::onRightTurnLeft(DWORD dt)
{
	if (headTurnRightAni->IsEnd())
		nextState = ON_LEFT;

	headAni = headTurnLeftAni;
	showCanon = false;
}

void CSophia::onLeftEjectJason(DWORD dt)
{
	if (headOnLeftEjectJasonAni->IsEnd())
		nextState = ON_LEFT;

	headAni = headOnLeftEjectJasonAni;
	showCanon = false;
}

void CSophia::onRightEjectJason(DWORD dt)
{
	if (headOnRightEjectJasonAni->IsEnd())
		nextState = ON_RIGHT;

	headAni = headOnRightEjectJasonAni;
	showCanon = false;
}

void CSophia::SetState(DWORD dt)
{
	if (keyLeft) pace = MOVE_LEFT;
	else if (keyRight) pace = MOVE_RIGHT;
	else pace = STILL;

	switch (state)
	{
	case ON_LEFT:
		onLeft(dt);
		break;
	case ON_RIGHT:
		onLeft(dt);
		break;

	case ON_LEFT_TURN_RIGHT:
		onLeftTurnRight(dt);
		break;
	case ON_RIGHT_TURN_LEFT:
		onRightTurnLeft(dt);
		break;

	case ON_LEFT_EJECT_JASON:
		onLeftEjectJason(dt);
		break;
	case ON_RIGHT_EJECT_JASON:
		onRightEjectJason(dt);
		break;
	default:
		break;
	}

	prevState = state;
	state = nextState;
}

void CSophia::GetState(DWORD dt)
{
	switch (pace)
	{
	case MOVE_RIGHT:
		leftWheelAni->SetMode(ANIMATION_NORMAL);
		rightWheelAni->SetMode(ANIMATION_NORMAL);
		break;
	case MOVE_LEFT:
		leftWheelAni->SetMode(ANIMATION_REVERSE);
		rightWheelAni->SetMode(ANIMATION_REVERSE);
		break;
	case STILL:
		leftWheelAni->SetMode(ANIMATION_PAUSE);
		rightWheelAni->SetMode(ANIMATION_PAUSE);
		break;
	}

	switch (face)
	{
	case FACE_LEFT:
		canonPivot = &leftCanonPivot;
		canonSprite = CSpriteLibrary::GetInstance()->Get(ID_SOPHIA_GUN_LEFT);

		leftWheelPivot = &leftWheelOnGroundPivot;
		rightWheelPivot = &rightWheelOnGroundPivot;
		break;
	case FACE_RIGHT:
		leftWheelPivot = &leftWheelOnGroundPivot;
		rightWheelPivot = &rightWheelOnGroundPivot;
		break;

	case FACE_UP_LEFT:
		leftWheelPivot = &leftWheelStandingPivot;
		rightWheelPivot = &rightWheelStandingPivot;
		break;
	case FACE_UP_RIGHT:
		leftWheelPivot = &leftWheelStandingPivot;
		rightWheelPivot = &rightWheelStandingPivot;
		break;
	default:
		break;
	}
}

CSophia::CSophia() : CPlayer()
{
	gravity = 0.3;
	jumpSpeed = 6.5;

	headPivot = &rightHeadPivot;
	canonPivot = &rightCanonPivot;

	this->collisionBox = new CDynamicBox(
		this,
		4, 11,
		22, 15
	);
	this->collisionBox->SetSolid(false);

	leftWheelAni = new CAnimation(1, 25);
	int idsL[] = {
		ID_SOPHIA_WHEEL_1,
		ID_SOPHIA_WHEEL_2,
		ID_SOPHIA_WHEEL_3,
		ID_SOPHIA_WHEEL_4,
	};
	leftWheelAni->Add(idsL, 4);

	rightWheelAni = new CAnimation(1, 25);
	int idsR[] = {
		ID_SOPHIA_WHEEL_4,
		ID_SOPHIA_WHEEL_1,
		ID_SOPHIA_WHEEL_2,
		ID_SOPHIA_WHEEL_3,
	};
	rightWheelAni->Add(idsR, 4);

	bodySprite = CSpriteLibrary::GetInstance()->Get(
		ID_SOPHIA_BODY
	);
}

void CSophia::Update(DWORD dt)
{
	CPlayer::Update(dt);

	CInput* input = CInput::GetInstance();

	keyUp = input->IsKeyDown(DIK_A);
	keyLeft = input->IsKeyDown(DIK_W);
	keyRight = input->IsKeyDown(DIK_D);
	keyDown = input->IsKeyDown(DIK_S);

	keyJump = input->IsKeyDown(DIK_J);
	keyShoot = input->IsKeyDown(DIK_K);
	keySwitchPlayer = input->IsKeyDown(DIK_L);

	velocity.x = dt * speed * (keyRight - keyLeft);

	if (onGround && keyUp)
		velocity.y = -jumpSpeed;

	SetState(dt);
	GetState(dt);

	HandleShooting(dt);

	old_velocity.Set(velocity.x, velocity.y);
	Move(dt);

	if (velocity.y < 0)
		onGround = false;
	else if (velocity.y == 0 && old_velocity.y > 0)
		onGround = true;


	/// <summary>
	/// health section
	/// </summary>
	CPlayerHealth* healthSystem = CPlayerHealth::GetInstance();
	if (IsCollidedWith(GOTYPES::Enemy) || IsCollidedWith(GOTYPES::EnemyBullet))
		healthSystem->ReduceHealth(GOTYPES::Sophia);

	if (healthSystem->GetHealthState() == INVULNERABLE)
		SetHealthAnimation(dt);
}

void CSophia::Render()
{
	if (!visible) return;

	Vector add_up = Vector(0, 0);
	if (!onGround) add_up.y = -2;

	leftWheelAni->Render(*leftWheelPivot + position);
	rightWheelAni->Render(*rightWheelPivot + position);

	headSprite->Draw(*headPivot + position + add_up);
	bodySprite->Draw(*bodyPivot + position + add_up);
	canonSprite->Draw(*canonPivot + position + add_up);
	collisionBox->Render();
}

void CSophia::SetHealthAnimation(DWORD dt)
{
	CSpriteLibrary* lib = CSpriteLibrary::GetInstance();

	//Get id of canon and head
	int canonSpriteId = canonSprite->GetId();
	int headSpriteId = headSprite->GetId();

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

	if (healthAniWhiteFlip)
	{
		canonSprite = lib->Get(canonSpriteId + 100);
		headSprite = lib->Get(headSpriteId + 100);
	}
}

void CSophia::Shoot()
{
	Vector* shoot_pivot = &shootRightPivot;
	Vector direction = Vector(0, 0);

	switch (face)
	{
	case SOPHIA_AIM_UPRIGHT:
		shoot_pivot = &shootUpRightPivot;
		direction.y = -1;
		break;
	case SOPHIA_AIM_UPLEFT:
		shoot_pivot = &shootUpLeftPivot;
		direction.y = -1;
		break;
	case SOPHIA_AIM_RIGHT:
		shoot_pivot = &shootRightPivot;
		direction.x = 1;
		break;
	case SOPHIA_AIM_LEFT:
		shoot_pivot = &shootLeftPivot;
		direction.x = -1;
		break;
	default:
		break;
	}

	float x = (*shoot_pivot).x + position.x;
	float y = (*shoot_pivot).y + position.y;

	try
	{
		LPRequest request = new CGameRequest(REQUEST_TYPES::CreateEntity);
		request->entity = new CPlayerBullet(
			direction
		);
		request->x = x;
		request->y = y;

		CGameRequest::AddRequest(request);
	}
	catch (const std::exception& ex)
	{
		DebugOut(L"[ERROR] create bullet %s \n", ex.what());
	}

	shootCountTime = 0;
	canShoot = false;
}
