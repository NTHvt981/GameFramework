#include "Player.h"

CPlayer* CPlayer::currentPlayer = NULL;

CPlayer::CPlayer(): CEntity()
{
	gravity = 0.3;
	jumpSpeed = 6.5;

	headPivot = &rightHeadPivot;
	canonPivot = &rightCanonPivot;

	SetType(GOTYPES::Player);
	camera = new CCamera(WINDOW_WIDTH, WINDOW_HEIGHT, 2);
	CCamera::SetInstance(*camera);

	this->collisionBox = new CDynamicBox(
		this,
		4, 11,
		22, 15
	);
	this->collisionBox->SetSolid(false);

	leftWheelAni = new CAnimation(1, 25);
	int idsL[] = {
		ID_CAR_WHEEL_1,
		ID_CAR_WHEEL_2,
		ID_CAR_WHEEL_3,
		ID_CAR_WHEEL_4,
	};
	leftWheelAni->Add(idsL, 4);

	rightWheelAni = new CAnimation(1, 25);
	int idsR[] = {
		ID_CAR_WHEEL_4,
		ID_CAR_WHEEL_1,
		ID_CAR_WHEEL_2,
		ID_CAR_WHEEL_3,
	};
	rightWheelAni->Add(idsR, 4);

	bodySprite = CSpriteLibrary::GetInstance()->Get(
		ID_CAR_BODY
	);

	CTimer* timer = new CTimer(1000);
	timer->Start();
}

void CPlayer::Update(DWORD dt)
{
	CInput* input = CInput::GetInstance();
	CPlayerHealth* healthSystem = CPlayerHealth::GetInstance();

	if (!enable) return;
	if (CPlayer::GetCurrentPlayer()->GetId() != GetId()) return;

	velocity.x = dt * speed * (
		input->IsKeyDown(DIK_D) - 
		input->IsKeyDown(DIK_A)
		);

	if (onGround)
		if (input->IsKeyDown(DIK_K))
		{
			velocity.y = -jumpSpeed;
		}

	/// <summary>
	/// For debugs
	/// </summary>
	/// <param name="dt"></param>
	if (input->IsKeyDown(DIK_J))
		healthSystem->ReduceHealth(GOTYPES::Sophia);

	SetState();
	GetState();

	old_velocity.Set(velocity.x, velocity.y);
	move(dt);

	if (velocity.y < 0)
		onGround = false;
	else if (velocity.y == 0 && old_velocity.y > 0)
		onGround = true;

	//float l, t, r, b;
	//collisionBox->GetLTRB(l, t, r, b);
	//center = Vector(
	//	(r + l) / 2,
	//	(b + t) / 2
	//);

	if (IsCollidedWith(GOTYPES::Enemy))
		healthSystem->ReduceHealth(GOTYPES::Sophia);

	if (healthSystem->GetHealthState() == INVULNERABLE)
		SetHealthAnimation(dt);
}

void CPlayer::Render()
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

CPlayer* CPlayer::GetCurrentPlayer()
{
	return currentPlayer;
}

void CPlayer::SetCurrentPlayer(CPlayer* player)
{
	currentPlayer = player;
}

void CPlayer::SetState()
{
	if (velocity.x > 0)
		horizontalState = PLAYER_MOVE_RIGHT;
	else if (velocity.x < 0)
		horizontalState = PLAYER_MOVE_LEFT;
	else
		horizontalState = PLAYER_DONT_MOVE;

	bool KeyW;
	KeyW = CInput::GetInstance()->IsKeyDown(DIK_W);

	if (KeyW)
	{
		if (velocity.x > 0 || aimDirection == PLAYER_AIM_RIGHT)
			aimDirection = PLAYER_AIM_UPRIGHT;
		else if (velocity.x < 0 || aimDirection == PLAYER_AIM_LEFT)
			aimDirection = PLAYER_AIM_UPLEFT;
	}
	else
	{
		if (velocity.x > 0)
			aimDirection = PLAYER_AIM_RIGHT;
		else if (velocity.x < 0)
			aimDirection = PLAYER_AIM_LEFT;
	}
}

void CPlayer::GetState()
{
	switch (horizontalState)
	{
	case PLAYER_MOVE_RIGHT:
		leftWheelAni->SetMode(ANIMATION_NORMAL);
		rightWheelAni->SetMode(ANIMATION_NORMAL);
		break;
	case PLAYER_MOVE_LEFT:
		leftWheelAni->SetMode(ANIMATION_REVERSE);
		rightWheelAni->SetMode(ANIMATION_REVERSE);
		break;
	case PLAYER_DONT_MOVE:
		leftWheelAni->SetMode(ANIMATION_PAUSE);
		rightWheelAni->SetMode(ANIMATION_PAUSE);
		break;
	}

	CSpriteLibrary* lib = CSpriteLibrary::GetInstance();
	switch (aimDirection)
	{
	case PLAYER_AIM_UPRIGHT:
		//set head & canon & body & wheel pivot (position)
		headPivot = &upRightHeadPivot;
		canonPivot = &upRightCanonPivot;
		bodyPivot = &bodyStandingPivot;
		leftWheelPivot = &leftWheelStandingPivot;
		rightWheelPivot = &rightWheelStandingPivot;

		//set head, canon, body sprite
		canonSprite = lib->Get(ID_CAR_GUN_UP);
		headSprite = lib->Get(ID_CAR_HEAD_UPRIGHT);
		bodySprite = lib->Get(ID_CAR_BODY_UPRIGHT);
		break;
	case PLAYER_AIM_UPLEFT:
		//set head & canon & body & wheel pivot (position)
		headPivot = &upLeftHeadPivot;
		canonPivot = &upLeftCanonPivot;
		bodyPivot = &bodyStandingPivot;
		leftWheelPivot = &leftWheelStandingPivot;
		rightWheelPivot = &rightWheelStandingPivot;

		//set head, canon, body sprite
		canonSprite = lib->Get(ID_CAR_GUN_UP);
		headSprite = lib->Get(ID_CAR_HEAD_UPLEFT);
		bodySprite = lib->Get(ID_CAR_BODY_UPLEFT);
		break;
	case PLAYER_AIM_RIGHT:
		//set head & canon & body & wheel pivot (position)
		headPivot = &rightHeadPivot;
		canonPivot = &rightCanonPivot;
		bodyPivot = &bodyOnGroundPivot;
		leftWheelPivot = &leftWheelOnGroundPivot;
		rightWheelPivot = &rightWheelOnGroundPivot;

		//set head, canon, body sprite
		canonSprite = lib->Get(ID_CAR_GUN_RIGHT);
		headSprite = lib->Get(ID_CAR_HEAD_RIGHT);
		bodySprite = lib->Get(ID_CAR_BODY);
		break;
	case PLAYER_AIM_LEFT:
		//set head & canon & body & wheel pivot (position)
		headPivot = &leftHeadPivot;
		canonPivot = &leftCanonPivot;
		bodyPivot = &bodyOnGroundPivot;
		leftWheelPivot = &leftWheelOnGroundPivot;
		rightWheelPivot = &rightWheelOnGroundPivot;

		//set head, canon, body sprite
		canonSprite = lib->Get(ID_CAR_GUN_LEFT);
		headSprite = lib->Get(ID_CAR_HEAD_LEFT);
		bodySprite = lib->Get(ID_CAR_BODY);
		break;
	default:
		break;
	}
}

void CPlayer::move(DWORD dt)
{
	//debug comment
	CEntity::move(dt);
#pragma region debug code

#pragma endregion
}

void CPlayer::SetHealthAnimation(DWORD dt)
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
			DebugOut(L"[INFO] flip white TRUE\n");
			healthAniWhiteFlip = false;
		}
		else
		{
			DebugOut(L"[INFO] flip white FALSE\n");
			healthAniWhiteFlip = true;
		}
	}

	if (healthAniWhiteFlip)
	{
		canonSprite = lib->Get(canonSpriteId + 100);
		headSprite = lib->Get(headSpriteId + 100);
	}

	//canonSprite = lib->Get(ID_CAR_GUN_UP);
	//headSprite = lib->Get(ID_CAR_HEAD_UPRIGHT);
}