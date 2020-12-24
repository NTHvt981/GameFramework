#include "IntroScene.h"

CIntroScene::CIntroScene(): CScene()
{
}

void CIntroScene::LoadResources()
{
	animation = new CAnimation(500, 1, false);
	animation->SetSpeed(8);

	animation->Add(ID_BLACK_SCREEN, 250);

	animation->Add(ID_OPENING_1, 150);
	animation->Add(ID_OPENING_2, 150);
	animation->Add(ID_OPENING_3, 200);
	animation->Add(ID_OPENING_4, 1000);
	animation->Add(ID_OPENING_3, 200);
	animation->Add(ID_OPENING_2, 150);
	animation->Add(ID_OPENING_1, 150);

	animation->Add(ID_BLACK_SCREEN, 250);

	animation->Add(ID_OPENING_5, 150);
	animation->Add(ID_OPENING_6, 150);
	animation->Add(ID_OPENING_7, 200);
	animation->Add(ID_OPENING_8, 1000);
	animation->Add(ID_OPENING_7, 200);
	animation->Add(ID_OPENING_6, 150);
	animation->Add(ID_OPENING_5, 150);

	animation->Add(ID_BLACK_SCREEN, 250);

	animation->Add(ID_OPENING_9, 150);
	animation->Add(ID_OPENING_10, 150);
	animation->Add(ID_OPENING_11, 200);
	animation->Add(ID_OPENING_12, 1000);
	animation->Add(ID_OPENING_11, 200);
	animation->Add(ID_OPENING_10, 150);
	animation->Add(ID_OPENING_9, 150);

	animation->Add(ID_BLACK_SCREEN, 250);

	animation->Add(ID_OPENING_13, 150);
	animation->Add(ID_OPENING_14, 150);
	animation->Add(ID_OPENING_15, 200);
	animation->Add(ID_OPENING_16, 500);
	animation->Add(ID_OPENING_17, 500);
	animation->Add(ID_OPENING_18, 500);
	animation->Add(ID_OPENING_19, 200);
	animation->Add(ID_OPENING_20, 150);
	animation->Add(ID_OPENING_21, 150);

	animation->Add(ID_BLACK_SCREEN, 250);

	animation->Add(ID_OPENING_22, 150);
	animation->Add(ID_OPENING_23, 150);
	animation->Add(ID_OPENING_24, 200);
	animation->Add(ID_OPENING_25, 1000);
	animation->Add(ID_OPENING_24, 200);
	animation->Add(ID_OPENING_23, 150);
	animation->Add(ID_OPENING_22, 150);

	animation->Add(ID_BLACK_SCREEN, 250);

	animation->Add(ID_OPENING_26, 150);
	animation->Add(ID_OPENING_27, 150);
	animation->Add(ID_OPENING_28, 200);
	animation->Add(ID_OPENING_29, 1000);
	animation->Add(ID_OPENING_28, 200);
	animation->Add(ID_OPENING_27, 150);
	animation->Add(ID_OPENING_26, 150);

	animation->Add(ID_BLACK_SCREEN, 250);

	animation->Add(ID_OPENING_30, 150);
	animation->Add(ID_OPENING_31, 150);
	animation->Add(ID_OPENING_32, 200);
	animation->Add(ID_OPENING_33, 1000);
	animation->Add(ID_OPENING_32, 200);
	animation->Add(ID_OPENING_31, 150);
	animation->Add(ID_OPENING_30, 150);

	animation->Add(ID_BLACK_SCREEN, 250);

	animation->Add(ID_OPENING_34, 150);
	animation->Add(ID_OPENING_35, 150);
	animation->Add(ID_OPENING_36, 200);
	animation->Add(ID_OPENING_37, 1000);
}

void CIntroScene::Start()
{
	CCamera::GetInstance()->FollowWithoutPlayer(0, 0);
}

void CIntroScene::Update(DWORD dt)
{
	if (animation->IsEnd())
	{
		LPGameRequest req = new CGameRequest(GAME_REQUEST_TYPES::SwitchToSideScroll);
		CGameRequest::AddRequest(req);
	}
}

void CIntroScene::Render()
{
	animation->Render(0.0, 0.0);
}

void CIntroScene::End()
{
}
