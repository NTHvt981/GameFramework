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

	switch (facing)
	{
	case FACE_LEFT:
		canonPivot = &leftCanonPivot;
		headPivot = &leftHeadPivot;
		bodyPivot = &bodyOnGroundPivot;
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
		bodyPivot = &bodyOnGroundPivot;
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
		bodyPivot = &bodyStandingPivot;
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
		bodyPivot = &bodyStandingPivot;
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
	speed = SOPHIA_MOVE_SPEED;
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

	leftWheelAni = new CAnimation(25);
	int idsL[] = {
		ID_SOPHIA_WHEEL_1,
		ID_SOPHIA_WHEEL_2,
		ID_SOPHIA_WHEEL_3,
		ID_SOPHIA_WHEEL_4,
	};
	leftWheelAni->Add(idsL, 4);

	rightWheelAni = new CAnimation(25);
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

	keyShoot = input->IsKeyDown(DIK_J);
	keySwitchPlayer = input->IsKeyPressed(DIK_L);

	/// <summary>
	/// Jump here
	/// </summary>
	//if (onGround && keyJump)
	//	velocity.y = -jumpSpeed;
	HandleMove(dt);
	HandleJump(dt);

	if (velocity.x > 0)
		pace = MOVE_RIGHT;
	else if (velocity.x < 0)
		pace = MOVE_LEFT;
	else
		pace = STILL;

	if (keyUp)
	{
		if (facing == FACE_RIGHT || keyRight)
			facing = FACE_UP_RIGHT;
		else if (facing == FACE_LEFT || keyLeft)
			facing = FACE_UP_LEFT;
	}
	else
	{
		if (keyRight) facing = FACE_RIGHT;
		else if (keyLeft) facing = FACE_LEFT;
	}

	//SetState(dt);
	GetState(dt);

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

	SetHealthAnimation(dt);
	HandleShooting(dt);
	HandleFiringMissile(dt);
	HandleSwitchToJason();
}

void CSophia::HandleMove(DWORD dt)
{
	int moveKey = keyRight - keyLeft;

	if (moveKey != 0)
		velocity.x += SOPHIA_MOVE_FRICTION * moveKey;
	else
	{
		if (velocity.x > 0)
			velocity.x = max(velocity.x - SOPHIA_MOVE_FRICTION, 0);
		else if (velocity.x < 0)
			velocity.x = min(velocity.x + SOPHIA_MOVE_FRICTION, 0);
	}

	if (velocity.x > SOPHIA_MOVE_SPEED)
		velocity.x = SOPHIA_MOVE_SPEED;
	else if (velocity.x < -SOPHIA_MOVE_SPEED)
		velocity.x = -SOPHIA_MOVE_SPEED;
}

void CSophia::HandleJump(DWORD dt)
{
	CInput* input = CInput::GetInstance();
	bool keyJump = input->IsKeyDown(DIK_K);
	bool keyJumpRelease = input->IsKeyRelease(DIK_K);

	if (onGround && keyJump)
	{
		jumpCountUp += dt;
		if (jumpCountUp >= bigJumpWaitTime)
			velocity.y = -SOPHIA_HIGH_JUMP_SPEED;
	}
	else if (onGround && keyJumpRelease)
	{
		if (jumpCountUp >= smallJumpWaitTime)
			velocity.y = -SOPHIA_MEDIUM_JUMP_SPEED;
		else
			velocity.y = -SOPHIA_LOW_JUMP_SPEED;
	}
	else
		jumpCountUp = 0;
}

void CSophia::HandleFiringMissile(DWORD dt)
{
	CInput* input = CInput::GetInstance();
	if (input->IsKeyPressed(DIK_I))
	{
		Vector center = GetCenter();

		CMissileSearcher* searcher = new CMissileSearcher();
		CMissile* missile = new CMissile(searcher);

		CSceneRequest* req = new CSceneRequest(SCENE_REQUEST_TYPES::CreateEntity);
		req->entity = searcher;
		req->x = center.x;
		req->y = center.y;
		CSceneRequest::AddRequest(req);

		LPSceneRequest request = new CSceneRequest(SCENE_REQUEST_TYPES::CreateEntity);
		request->entity = missile;
		request->x = center.x;
		request->y = center.y;
		CSceneRequest::AddRequest(request);
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
	bodySprite->Draw(*bodyPivot + position + add_up);
	if (showCanon) canonSprite->Draw(*canonPivot + position + add_up);
	collisionBox->Render();
}

void CSophia::SetHealthAnimation(DWORD dt)
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

	switch (facing)
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
		LPSceneRequest request = new CSceneRequest(SCENE_REQUEST_TYPES::CreateEntity);
		request->entity = new CSophiaBullet(
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
}

void CSophia::HandleSwitchToJason()
{
	if (keySwitchPlayer && onGround && pace == STILL)
	{
		if (facing != FACE_LEFT && facing != FACE_RIGHT)
			return;

		CSophiaFake* faker = CSophiaFake::GetInstance();

		faker->canonPivot = *canonPivot;
		faker->headPivot = *headPivot;
		faker->bodyPivot = *bodyPivot;
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

		if (facing == FACE_LEFT)
		{
			jason->SetFacing(LEFT);

			center = center + ejectJasonLeftPivot;
		}
		else if (facing == FACE_RIGHT)
		{
			jason->SetFacing(RIGHT);

			center = center + ejectJasonRightPivot;
		}
		jason->SetCenter(
			center.x,
			center.y
		);

		LPSceneRequest switchJasonReq = new CSceneRequest(SCENE_REQUEST_TYPES::SwitchToJason);
		CSceneRequest::AddRequest(switchJasonReq);

		LPSceneRequest fakeSophiaReq = new CSceneRequest(SCENE_REQUEST_TYPES::CreateEntity);
		fakeSophiaReq->entity = faker;
		fakeSophiaReq->x = position.x;
		fakeSophiaReq->y = position.y;

		CSceneRequest::AddRequest(fakeSophiaReq);
	}
}

CSophia* CSophia::GetInstance()
{
	if (__instance == NULL)
		__instance = new CSophia();

	return __instance;
}
