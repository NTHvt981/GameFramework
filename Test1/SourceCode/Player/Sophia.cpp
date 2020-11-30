#include "Sophia.h"

CSophia* CSophia::__instance = NULL;

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
		headPivot = &leftHeadPivot;
		leftWheelPivot = &leftWheelOnGroundPivot;
		rightWheelPivot = &rightWheelOnGroundPivot;

		canonSprite = CSpriteLibrary::GetInstance()->Get(ID_SOPHIA_GUN_LEFT);
		headSprite = CSpriteLibrary::GetInstance()->Get(ID_SOPHIA_HEAD_LEFT);

		leftWheelPivot = &leftWheelOnGroundPivot;
		rightWheelPivot = &rightWheelOnGroundPivot;
		break;
	case FACE_RIGHT:
		canonPivot = &rightCanonPivot;
		headPivot = &rightHeadPivot;
		leftWheelPivot = &leftWheelOnGroundPivot;
		rightWheelPivot = &rightWheelOnGroundPivot;

		canonSprite = CSpriteLibrary::GetInstance()->Get(ID_SOPHIA_GUN_RIGHT);
		headSprite = CSpriteLibrary::GetInstance()->Get(ID_SOPHIA_HEAD_RIGHT);

		leftWheelPivot = &leftWheelOnGroundPivot;
		rightWheelPivot = &rightWheelOnGroundPivot;
		break;

	case FACE_UP_LEFT:
		canonPivot = &upLeftCanonPivot;
		headPivot = &upLeftHeadPivot;
		leftWheelPivot = &leftWheelStandingPivot;
		rightWheelPivot = &rightWheelStandingPivot;

		canonSprite = CSpriteLibrary::GetInstance()->Get(ID_SOPHIA_GUN_UP);
		headSprite = CSpriteLibrary::GetInstance()->Get(ID_SOPHIA_HEAD_UPLEFT);

		leftWheelPivot = &leftWheelStandingPivot;
		rightWheelPivot = &rightWheelStandingPivot;
		break;
	case FACE_UP_RIGHT:
		canonPivot = &upRightCanonPivot;
		headPivot = &upRightHeadPivot;
		leftWheelPivot = &leftWheelStandingPivot;
		rightWheelPivot = &rightWheelStandingPivot;

		canonSprite = CSpriteLibrary::GetInstance()->Get(ID_SOPHIA_GUN_UP);
		headSprite = CSpriteLibrary::GetInstance()->Get(ID_SOPHIA_HEAD_UPRIGHT);

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

	keyUp = input->IsKeyDown(DIK_W);
	keyLeft = input->IsKeyDown(DIK_A);
	keyRight = input->IsKeyDown(DIK_D);
	keyDown = input->IsKeyDown(DIK_S);

	keyJump = input->IsKeyDown(DIK_K);
	keyShoot = input->IsKeyDown(DIK_J);
	keySwitchPlayer = input->IsKeyPressed(DIK_L);

	velocity.x = dt * speed * (keyRight - keyLeft);

	if (onGround && keyJump)
		velocity.y = -jumpSpeed;

	if (keyRight)
		pace = MOVE_RIGHT;
	else if (keyLeft)
		pace = MOVE_LEFT;
	else
		pace = STILL;

	if (keyUp)
	{
		if (face == FACE_RIGHT || keyRight)
			face = FACE_UP_RIGHT;
		else if (face == FACE_LEFT || keyLeft)
			face = FACE_UP_LEFT;
	}
	else
	{
		if (keyRight) face = FACE_RIGHT;
		else if (keyLeft) face = FACE_LEFT;
	}

	//SetState(dt);
	GetState(dt);

	HandleShooting(dt);
	HandleSwitchToJason();

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
	else
	{
		showCanon = true;
		showHead = true;
	}
}

void CSophia::Render()
{
	if (!visible) return;

	Vector add_up = Vector(0, 0);
	if (!onGround) add_up.y = -2;

	leftWheelAni->Render(*leftWheelPivot + position);
	rightWheelAni->Render(*rightWheelPivot + position);

	if (showHead) headSprite->Draw(*headPivot + position + add_up);
	bodySprite->Draw(bodyPivot + position + add_up);
	if (showCanon) canonSprite->Draw(*canonPivot + position + add_up);
	collisionBox->Render();
}

void CSophia::SetHealthAnimation(DWORD dt)
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

	if (healthAniWhiteFlip)
	{
		showCanon = false;
		showHead = false;
	}
	else
	{
		showCanon = true;
		showHead = true;
	}
}

void CSophia::Shoot()
{
	Vector* shoot_pivot = &shootRightPivot;
	Vector direction = Vector(0, 0);

	switch (face)
	{
	case FACE_UP_RIGHT:
		shoot_pivot = &shootUpRightPivot;
		direction.y = -1;
		break;
	case FACE_UP_LEFT:
		shoot_pivot = &shootUpLeftPivot;
		direction.y = -1;
		break;
	case FACE_RIGHT:
		shoot_pivot = &shootRightPivot;
		direction.x = 1;
		break;
	case FACE_LEFT:
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

void CSophia::HandleSwitchToJason()
{
	if (keySwitchPlayer)
	{
		if (face != FACE_LEFT && face != FACE_RIGHT)
			return;

		CSophiaFake* faker = CSophiaFake::GetInstance();

		faker->canonPivot = *canonPivot;
		faker->headPivot = *headPivot;
		faker->bodyPivot = bodyPivot;
		faker->leftWheelPivot = *leftWheelPivot;
		faker->rightWheelPivot = *rightWheelPivot;

		faker->canonSprite = canonSprite;
		faker->headSprite = headSprite;
		faker->bodySprite = bodySprite;
		faker->leftWheelAni = leftWheelAni;
		faker->rightWheelAni = rightWheelAni;

		faker->realSophiaId = GetId();

		CJason* jason = CJason::GetInstance();
		Vector center = GetPosition();

		if (face == FACE_LEFT)
		{
			jason->SetFacing(LEFT);

			center = center + ejectJasonLeftPivot;
		}
		else if (face == FACE_RIGHT)
		{
			jason->SetFacing(RIGHT);

			center = center + ejectJasonRightPivot;
		}
		jason->SetCenter(
			center.x,
			center.y
		);

		LPRequest switchJasonReq = new CGameRequest(REQUEST_TYPES::SwitchToJason);
		CGameRequest::AddRequest(switchJasonReq);

		LPRequest fakeSophiaReq = new CGameRequest(REQUEST_TYPES::CreateEntity);
		fakeSophiaReq->entity = faker;
		fakeSophiaReq->x = position.x;
		fakeSophiaReq->y = position.y;

		CGameRequest::AddRequest(fakeSophiaReq);
	}
}

CSophia* CSophia::GetInstance()
{
	if (__instance == NULL)
		__instance = new CSophia();

	return __instance;
}
