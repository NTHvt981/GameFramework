#include "BossScene.h"

CBossScene::CBossScene() : CScene()
{

}

void CBossScene::Start()
{
	boss->SetCenter(width / 2, height / 4);

	CJasonTopDown::GetInstance()->SetCenter(width / 2, height * 3 / 4);
	CCamera::GetInstance()->SetOuterBound(0, 0, width, height);
	CCamera::GetInstance()->Follow(width / 2, height / 2);
}

void CBossScene::LoadResources()
{
	boss = new CBoss(&gameOver);
}

void CBossScene::Update(DWORD dt)
{
	CInput::GetInstance()->Update();

	boss->Update(dt);
	CJasonTopDown::GetInstance()->Update(dt);

	CJasonTopDown* player = CJasonTopDown::GetInstance();
	CCamera* camera = CCamera::GetInstance();
}

void CBossScene::Render()
{
	boss->Render();
	CJasonTopDown::GetInstance()->Render();

	CPlayerHealth::GetInstance()->Render();
}

void CBossScene::End()
{

}