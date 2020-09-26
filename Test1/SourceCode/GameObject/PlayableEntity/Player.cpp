#include "Player.h"

CPlayer::CPlayer(LPCWSTR texturePath): CGameObject(texturePath)
{
	camera = new CCamera(0, 0);
	CCamera::SetInstance(*camera);

	this->collisionBox = new CCollisionBox(
		this,
		0.0f, 0.0f,
		17.0f, 18.0f
	);
}

void CPlayer::Update(DWORD dt)
{
	//DebugOut(L"[DEBUG] Player collision\n left %f | right %f | top %f | bottom %f\n", 
	//	collisionBox->GetLeft(), collisionBox->GetRight(),
	//	collisionBox->GetTop(), collisionBox->GetBottom());

	velocity.x = dt * speed * (
		CInput::GetInstance()->IsKeyDown(DIK_D) - CInput::GetInstance()->IsKeyDown(DIK_A)
		);
	velocity.y = dt * speed * (
		-CInput::GetInstance()->IsKeyDown(DIK_S) + CInput::GetInstance()->IsKeyDown(DIK_W)
		);

	move(dt);

	if (position.x < 0) position.x = 0;
	if (position.x > WINDOW_WIDTH) position.x = WINDOW_WIDTH;
	if (position.y < 0) position.y = 0;
	if (position.y > WINDOW_HEIGHT) position.y = WINDOW_HEIGHT;

	camera->SetPosition(Vector(position.x - WINDOW_WIDTH / 2, position.y + WINDOW_HEIGHT / 2));
}
