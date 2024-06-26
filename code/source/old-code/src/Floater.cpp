#include "Floater.h"

void CFloater::FloatDiagonal(DWORD dt)
{
	velocity.x = horFacing * diagonalSpeed;
	velocity.y = verFacing * diagonalSpeed;

	Move(dt);

	if (collisionBox->IsHypothesizedColliding(
		position.x + horFacing, position.y
	))
		horFacing = -horFacing;

	if (collisionBox->IsHypothesizedColliding(
		position.x, position.y + verFacing
	))
		verFacing = -verFacing;
}

void CFloater::FloatHorizontal(DWORD dt)
{
	velocity.x = horFacing * horizontalSpeed;
	velocity.y = 0;

	Move(dt);

	if (collisionBox->IsHypothesizedColliding(
		position.x + horFacing, position.y
	))
		horFacing = -horFacing;
}

void CFloater::FloatVertical(DWORD dt)
{
	velocity.x = 0;
	velocity.y = verFacing * verticalSpeed;

	Move(dt);

	if (collisionBox->IsHypothesizedColliding(
		position.x, position.y + verFacing
	))
		verFacing = -verFacing;
}

CFloater::CFloater(int64_t _type)
{
	SetType(GOTYPES::Enemy);
	floaterType = _type;
	if (_type == FLOATER_DIAGONAL)
		velocity.Set(1 * diagonalSpeed, 1 * diagonalSpeed);

	animation = new CAnimation(150);
	int64_t idsR[] = {
		ID_FLOATER_MOVE_1,
		ID_FLOATER_MOVE_2
	};

	animation->Add(idsR, 2);

	animation->GetSize(width, height);
	this->collisionBox = new CDynamicBox(
		this,
		0, 0,
		width, height
	);
	collisionBox->SetSolid(false);
}

void CFloater::Update(DWORD dt)
{
	switch (floaterType)
	{
	case FLOATER_DIAGONAL:
		FloatDiagonal(dt);
		break;
	case FLOATER_HORIZONTAL:
		FloatHorizontal(dt);
		break;
	case FLOATER_VERTICAL:
		FloatVertical(dt);
		break;
	}
}

void CFloater::Render()
{
	animation->Render(position.x, position.y);
	collisionBox->Render();
}
