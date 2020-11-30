#include "SophiaFake.h"

CSophiaFake* CSophiaFake::__instance = NULL;

CSophiaFake::CSophiaFake() : CEntity()
{
	SetType(GOTYPES::FakeSophia);

	this->collisionBox = new CDynamicBox(
		this,
		4, 11,
		22, 15
	);
	collisionBox->SetSolid(false);
}

void CSophiaFake::Render() 
{
	if (!enable) return;

	leftWheelAni->Render(leftWheelPivot + position);
	rightWheelAni->Render(rightWheelPivot + position);

	bodySprite->Draw(bodyPivot + position);
	headSprite->Draw(headPivot + position);
	canonSprite->Draw(canonPivot + position);

	collisionBox->Render();
}

CSophiaFake* CSophiaFake::GetInstance()
{
	if (__instance == NULL)
		__instance = new CSophiaFake();

	return __instance;
}
