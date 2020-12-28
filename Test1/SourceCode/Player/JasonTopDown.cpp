#include "JasonTopDown.h"

CJasonTopDown* CJasonTopDown::__instance = NULL;

void CJasonTopDown::SetFacing(int _facing)
{
	facing = _facing;
}

CJasonTopDown::CJasonTopDown(int _facing, int _pace)
{
	facing = _facing;
	pace = _pace;

	collisionBox = new CDynamicBox(
		this,
		2, 15,
		20, 16
	);
	collisionBox->SetSolid(false);

	CSpriteLibrary* lib = CSpriteLibrary::GetInstance();

	walkLeftAnimation = new CAnimation(JASON_TOPDOWN_FRAME_TIME);
	int ids1[] = {
		ID_JASON_TOPDOWN_WALK_LEFT_1,
		ID_JASON_TOPDOWN_WALK_LEFT_2,
		ID_JASON_TOPDOWN_WALK_LEFT_3,
	};
	walkLeftAnimation->Add(ids1, 3);

	walkRightAnimation = new CAnimation(JASON_TOPDOWN_FRAME_TIME);
	int ids2[] = {
		ID_JASON_TOPDOWN_WALK_RIGHT_1,
		ID_JASON_TOPDOWN_WALK_RIGHT_2,
		ID_JASON_TOPDOWN_WALK_RIGHT_3,
	};
	walkRightAnimation->Add(ids2, 3);

	walkUpAnimation = new CAnimation(JASON_TOPDOWN_FRAME_TIME);
	int ids3[] = {
		ID_JASON_TOPDOWN_WALK_UP_1,
		ID_JASON_TOPDOWN_WALK_UP_2,
		ID_JASON_TOPDOWN_WALK_UP_3,
	};
	walkUpAnimation->Add(ids3, 3);

	walkDownAnimation = new CAnimation(JASON_TOPDOWN_FRAME_TIME);
	int ids4[] = {
		ID_JASON_TOPDOWN_WALK_DOWN_1,
		ID_JASON_TOPDOWN_WALK_DOWN_2,
		ID_JASON_TOPDOWN_WALK_DOWN_3,
	};
	walkDownAnimation->Add(ids4, 3);

	animation = walkRightAnimation;
}

void CJasonTopDown::Update(DWORD dt)
{
	CPlayer::Update(dt);

	CInput* input = CInput::GetInstance();

	keyUp = input->IsKeyDown(DIK_W);
	keyLeft = input->IsKeyDown(DIK_A);
	keyRight = input->IsKeyDown(DIK_D);
	keyDown = input->IsKeyDown(DIK_S);

	keyShoot = input->IsKeyDown(DIK_J);

	int hKey = keyRight - keyLeft;
	int vKey = keyDown - keyUp;

	if (hKey != 0)
	{
		if (keyRight && vKey == 0 && !keyShoot)
			facing = RIGHT;
		else if (keyLeft && vKey == 0 && !keyShoot)
			facing = LEFT;

		pace = MOTION;
	}

	if (vKey != 0)
	{
		if (keyDown && hKey == 0 && !keyShoot)
			facing = DOWN;
		else if (keyUp && hKey == 0 && !keyShoot)
			facing = UP;

		pace = MOTION;
	}
	
	if (hKey == 0 && vKey == 0)
		pace = STILL;

	velocity.x = hKey * speed;
	velocity.y = vKey * speed;

	Move(dt);

	GetSetAnimation(dt, facing, pace);

	CPlayerHealth* healthSystem = CPlayerHealth::GetInstance();
	if (IsCollidedWith(GOTYPES::Enemy) || IsCollidedWith(GOTYPES::EnemyBullet))
		healthSystem->ReduceHealth(GOTYPES::Jason);

	SetHealthAnimation(dt);

	HandleShooting(dt);
	HandleAreaTransitioning(dt);
}

void CJasonTopDown::Render()
{
	if (!visible) return;

	if (showAnimation)
		animation->Render(
			position.x + posToDraw->x,
			position.y + posToDraw->y
		);

	collisionBox->Render();
}

void CJasonTopDown::SetHealthAnimation(DWORD dt)
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

void CJasonTopDown::GetSetAnimation(DWORD dt, int _facing, int _pace)
{
	switch (_facing)
	{
	case LEFT:
		animation = walkLeftAnimation;

		posToDraw = &posHorSpr;
		break;
	case UP:
		animation = walkUpAnimation;

		posToDraw = &posVerSpr;
		break;
	case RIGHT:
		animation = walkRightAnimation;

		posToDraw = &posHorSpr;
		break;
	case DOWN:
		animation = walkDownAnimation;

		posToDraw = &posVerSpr;
		break;
	default:
		break;
	}

	if (_pace == STILL)
	{
		animation->SetMode(ANIMATION_PAUSE);
	}
	else if (_pace == MOTION)
		animation->SetMode(ANIMATION_NORMAL);
}

void CJasonTopDown::Shoot()
{
	Vector direction = Vector(0, 0);
	Vector *shootPivot = new Vector(0, 0);

	if (facing == RIGHT)
	{
		direction = Vector(1, 0);
		shootPivot = &rightShootPivot;
	}
	else if (facing == LEFT)
	{
		direction = Vector(-1, 0);
		shootPivot = &leftShootPivot;
	}
	else if (facing == UP)
	{
		direction = Vector(0, -1);
		shootPivot = &upShootPivot;
	}
	else if (facing == DOWN)
	{
		direction = Vector(0, 1);
		shootPivot = &downShootPivot;
	}

	float x = GetCenter().x;
	float y = GetCenter().y;

	try
	{
		LPSceneRequest request = new CSceneRequest(SCENE_REQUEST_TYPES::CreateEntity);
		request->entity = new CJasonTopDownBullet(
			direction
		);
		request->x = x + shootPivot->x;
		request->y = y + shootPivot->y;

		CSceneRequest::AddRequest(request);
	}
	catch (const std::exception& ex)
	{
		DebugOut(L"[ERROR] create bullet %s \n", ex.what());
	}

	shootCountTime = 0;
	canShoot = false;
}

CJasonTopDown* CJasonTopDown::GetInstance()
{
	if (__instance == NULL)
		__instance = new CJasonTopDown();

	return __instance;
}

void CJasonTopDown::HandleAreaTransitioning(DWORD dt)
{
	if (IsCollidedWith(GOTYPES::AreaPortal))
	{
		list<LPGameObject> objs;
		GetCollidedWith(GOTYPES::AreaPortal, objs);

		LPEntity portal = dynamic_cast<LPEntity>(objs.front());

		LPSceneRequest request = new CSceneRequest(SCENE_REQUEST_TYPES::SwitchArea);
		request->entity = portal;

		CSceneRequest::AddRequest(request);
	}
}
