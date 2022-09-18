#include "EndingScene.h"

CEndingScene::CEndingScene()
{
	Type = SCENE_TYPES::EndingScene;
}

void CEndingScene::LoadResources()
{
	animation = new CAnimation(500, 1, false);

	animation->Add(ID_ROLLOUT_1, 1000);
	animation->Add(ID_ROLLOUT_2, 500);
	animation->Add(ID_ROLLOUT_3, 50);
	animation->Add(ID_ROLLOUT_4, 75);
	animation->Add(ID_ROLLOUT_5, 100);
	animation->Add(ID_ROLLOUT_6, 150);
	animation->Add(ID_ROLLOUT_7, 50);
	animation->Add(ID_ROLLOUT_8, 75);
	animation->Add(ID_ROLLOUT_9, 100);
	animation->Add(ID_ROLLOUT_10, 150);
	animation->Add(ID_ROLLOUT_7, 250);
}

void CEndingScene::Start()
{
	CCamera::GetInstance()->FollowWithoutPlayer(0, 0);
}

void CEndingScene::Update(DWORD dt)
{
}

void CEndingScene::Render()
{
	animation->Render(0.0, 0.0);
}

void CEndingScene::End()
{
}
