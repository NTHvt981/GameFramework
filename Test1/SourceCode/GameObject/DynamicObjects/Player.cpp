#include "Player.h"

CPlayer* CPlayer::currentPlayer = NULL;

CPlayer::CPlayer(): CEntity()
{
	gravity = 0.25;
	jumpSpeed = 6.5;

	SetType(GOTYPES::Player);
	camera = new CCamera(CAMERA_WIDTH, CAMERA_HEIGHT, 1);
	CCamera::SetInstance(*camera);

	this->collisionBox = new CDynamicBox(
		this,
		-12, 8,
		24, 16
	);

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
	velocity.x = dt * speed * (
		CInput::GetInstance()->IsKeyDown(DIK_D) - CInput::GetInstance()->IsKeyDown(DIK_A)
		);
	if (onGround)
		if (CInput::GetInstance()->IsKeyDown(DIK_K))
		{
			velocity.y = jumpSpeed;
		}

	SetState();
	GetState();

	old_velocity.Set(velocity.x, velocity.y);
	move(dt);

	if (velocity.y > 0)
		onGround = false;
	else if (velocity.y == 0 && old_velocity.y < 0)
		onGround = true;

	//if (position.x < 0) position.x = 0;
	//if (position.x > WINDOW_WIDTH) position.x = WINDOW_WIDTH;
	//if (position.y < 0) position.y = 0;
	//if (position.y > WINDOW_HEIGHT) position.y = WINDOW_HEIGHT;

	camera->Follow(position.x, position.y);

}

void CPlayer::Render()
{
	leftWheelAni->Render(leftWheelPivot + position);
	rightWheelAni->Render(rightWheelPivot + position);

	headSprite->Draw(headPivot + position);
	bodySprite->Draw(bodyPivot + position);
	canonSprite->Draw(canonPivot + position);
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
		canonSprite = lib->Get(ID_CAR_GUN_UP);
		headSprite = lib->Get(ID_CAR_HEAD_UPRIGHT);
		break;
	case PLAYER_AIM_UPLEFT:
		canonSprite = lib->Get(ID_CAR_GUN_UP);
		headSprite = lib->Get(ID_CAR_HEAD_UPLEFT);
		break;
	case PLAYER_AIM_RIGHT:
		canonSprite = lib->Get(ID_CAR_GUN_RIGHT);
		headSprite = lib->Get(ID_CAR_HEAD_RIGHT);
		break;
	case PLAYER_AIM_LEFT:
		canonSprite = lib->Get(ID_CAR_GUN_LEFT);
		headSprite = lib->Get(ID_CAR_HEAD_LEFT);
		break;
	default:
		break;
	}
}
