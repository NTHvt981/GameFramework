#include "Boss.h"

CBoss::CBoss(bool* overCon)
{
	SetType(GOTYPES::Enemy);
	gameOver = overCon;

	animation = new CAnimation(1, 500);
	animation->Add(ID_BOSS_HEAD_1);
	animation->Add(ID_BOSS_HEAD_2);
	animation->Add(ID_BOSS_HEAD_3);
	animation->Add(ID_BOSS_HEAD_4);
	animation->Add(ID_BOSS_HEAD_5);
	animation->Add(ID_BOSS_HEAD_6);
	animation->Add(ID_BOSS_HEAD_7);
	animation->Add(ID_BOSS_HEAD_8);

	animation->GetSize(width, height);
	collisionBox = new CDynamicBox(
		this,
		-width / 2, -height / 2,
		width, height
	);

	leftHand = new CBossHand(
		ID_BOSS_LEFT_HAND);
	rightHand = new CBossHand(
		ID_BOSS_RIGHT_HAND);

	debugMatrix.push_back(Vector(100, 0));
	debugMatrix.push_back(Vector(100, 100));
	debugMatrix.push_back(Vector(0, 100));
	debugMatrix.push_back(Vector(0, 0));
	debugMatrix.push_back(Vector(100, 0));
	debugMatrix.push_back(Vector(0, 100));
	debugMatrix.push_back(Vector(-50, 100));
	debugMatrix.push_back(Vector(-100, 0));
	debugMatrix.push_back(Vector(0, 0));
	debugMatrix.push_back(Vector(0, -100));
	debugMatrix.push_back(Vector(0, 0));

	rightHand->SetGoalPosition(debugMatrix[index].x, debugMatrix[index].y);
}

void CBoss::Update(DWORD dt)
{
	rightHand->Update(dt);

	if (rightHand->HasReachGoal())
	{
		index++;

		if (index > debugMatrix.size() - 1)
			index = 0;

		rightHand->SetGoalPosition(debugMatrix[index].x, debugMatrix[index].y);
	}
}

void CBoss::Render()
{
	animation->Render(
		position.x - width / 2,
		position.y - height / 2
	);
	collisionBox->Render();

	leftHand->Render();
	rightHand->Render();
}

void CBoss::SetCenter(float _x, float _y)
{
	SetPosition(_x, _y);

	leftHand->SetPosition(
		position.x + leftHandPivot.x,
		position.y + leftHandPivot.y);
	rightHand->SetPosition(
		position.x + rightHandPivot.x,
		position.y + rightHandPivot.y);
}
