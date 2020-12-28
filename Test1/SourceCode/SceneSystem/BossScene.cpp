#include "BossScene.h"

void CBossScene::ExecuteRequests()
{
	list<LPSceneRequest> requests = CSceneRequest::RequestList;

	while (!requests.empty())
	{
		LPSceneRequest re = requests.front();

		ExecuteRequest(re);
		requests.pop_front();
	}
}

void CBossScene::ExecuteRequest(LPSceneRequest request)
{
	switch (request->Type)
	{
	case SCENE_REQUEST_TYPES::CreateEntity:
		AddEntity(
			request->entity,
			request->x,
			request->y
		);
		break;
	case SCENE_REQUEST_TYPES::DeleteEntity:
		RemoveEntity(request->id);
		break;
	default:
		break;
	}
}

void CBossScene::AddEntity(LPEntity entity, float x, float y)
{
	entity->SetCenter(x, y);

	entity->SetId(countId);
	mapEntities[countId] = entity;
	countId++;

	ResetEntityCoCollisionBoxes(entity);
}

void CBossScene::RemoveEntity(int id)
{
	LPEntity entity = mapEntities[id];

	mapEntities.erase(id);
	free(entity);
}

void CBossScene::UpdateOtherEntities(DWORD dt)
{
	for each (pair<int, CEntity*> p in mapEntities)
	{
		p.second->Update(dt);
	}
}

void CBossScene::RenderOtherEntities()
{
	for each (pair<int, CEntity*> p in mapEntities)
	{
		p.second->Render();
	}
}

void CBossScene::ResetEntityCoCollisionBoxes(LPEntity entity)
{
	list<LPCollisionBox> lst;
	boss->GetAllCollisionBoxes(lst);
	lst.push_back(CPlayer::GetCurrentPlayer()->GetCollisionBox());
	entity->GetCollisionBox()->ResetCoCollisionBoxes(lst);
}

void CBossScene::NormalState(DWORD dt)
{
	boss->Update(dt);
	CJasonTopDown::GetInstance()->Update(dt);
	CPlayerHealth::GetInstance()->Update(dt);

	UpdateOtherEntities(dt);

	if (boss->IsDefeat())
		state = BOSS_DEFEAT;
}

void CBossScene::DefeatState(DWORD dt)
{
	boss->Update(dt);
	UpdateOtherEntities(dt);

	winCountUp += dt;
	if (winCountUp >= winWaitTime)
	{
		winCountUp = 0;

		LPGameRequest request = new CGameRequest(GAME_REQUEST_TYPES::SwitchToSideScroll);
		request->sender = SCENE_TYPES::BossScene;

		CGameRequest::AddRequest(request);
	}
}

CBossScene::CBossScene() : CScene()
{
	Type = SCENE_TYPES::BossScene;
}

void CBossScene::Start(float x, float y)
{
	boss->Reset();
	boss->SetCenter(width / 2, height / 4);
	state = BOSS_NORMAL;

	CJasonTopDown::GetInstance()->SetCenter(x, y);
	CCamera::GetInstance()->SetOuterBound(0, 0, width, height);
	CCamera::GetInstance()->Follow(width / 2, height / 2);

	list<LPCollisionBox> lst;
	boss->GetAllCollisionBoxes(lst);
	CJasonTopDown::GetInstance()->GetCollisionBox()
		->ResetCoCollisionBoxes(
			lst
		);

	CPlayerHealth::GetInstance()->SetPlayerMode(JASON);
}

void CBossScene::ReStart(float x, float y)
{
	Start(x, y);
}

void CBossScene::LoadResources()
{
	boss = new CBoss();
}

void CBossScene::Update(DWORD dt)
{
	CInput::GetInstance()->Update();
	CSceneRequest::RequestList.clear();

	switch (state)
	{
	case BOSS_NORMAL:
		NormalState(dt);
		break;
	case BOSS_DEFEAT:
		DefeatState(dt);
		break;
	default:
		break;
	}
}

void CBossScene::Render()
{
	boss->Render();
	CJasonTopDown::GetInstance()->Render();

	CPlayerHealth::GetInstance()->Render();

	RenderOtherEntities();
	ExecuteRequests();
}

void CBossScene::End()
{

}