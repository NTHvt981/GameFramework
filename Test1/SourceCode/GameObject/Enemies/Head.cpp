#include "Head.h"

CHead::CHead()
{
	animation = new CAnimation(750);

	if (CUtils::lottery(0.5))
	{
		animation->Add(ID_HEAD_LEFT_1);
		animation->Add(ID_HEAD_LEFT_2);
	}
	else
	{
		animation->Add(ID_HEAD_RIGHT_1);
		animation->Add(ID_HEAD_RIGHT_2);
	}

	animation->GetSize(width, height);

	collisionBox = new CDynamicBox(
		this, 0, 0,
		width, height
	);
	collisionBox->SetSolid(true);
}

void CHead::Update(DWORD dt)
{
	if (InPlayerZone())
	{
		Vector center = GetCenter();
		Vector playerCenter = CPlayer::GetCurrentPlayer()->GetCenter();
		float distance = DistanceToPlayer();

		velocity.x = (playerCenter.x - center.x) / distance * speed;
		velocity.y = (playerCenter.y - center.y) / distance * speed;

		Move(dt);
	}
}

void CHead::Render()
{
	animation->Render(position.x, position.y);
	collisionBox->Render();
}
