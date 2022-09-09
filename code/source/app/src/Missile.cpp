#include "Missile.h"

void CMissileSearcher::Follow(float x, float y)
{
	position.Set(x, y);
	collisionBox->Update();
	collisionBox->GetCollision(collideEvents);
}

std::list<LPEntity> CMissileSearcher::GetTargets()
{
	std::list<LPEntity> results;

	for (const CollisionEvent& e: collideEvents)
	{
		if (e.object->GetType() == GOTYPES::Enemy)
		{
			results.push_back(dynamic_cast<LPEntity>(e.object));
		}
	}

	return results;
}

CMissileSearcher::CMissileSearcher(): CEntity()
{
	collisionBox = new CDynamicBox(
		this,
		-MISSILE_SEARCH_RANGE / 2,
		-MISSILE_SEARCH_RANGE / 2,
		MISSILE_SEARCH_RANGE,
		MISSILE_SEARCH_RANGE
	);
	collisionBox->SetSolid(false);

	velocity.Set(0, 0);
}

void CMissileSearcher::Update(DWORD dt)
{
	Move(dt);
}

void CMissileSearcher::Render()
{
	//collisionBox->Render();
}

CMissile::CMissile(CMissileSearcher* s, float dir_x, float dir_y)
{
	searcher = s;

	CSpriteLibrary* lib = CSpriteLibrary::GetInstance();

	headLeft = lib->Get(ID_SOPHIA_MISSILE_HEAD_LEFT);
	headUp = lib->Get(ID_SOPHIA_MISSILE_HEAD_UP);
	headRight = lib->Get(ID_SOPHIA_MISSILE_HEAD_RIGHT);
	headDown = lib->Get(ID_SOPHIA_MISSILE_HEAD_DOWN);

	tailLeft = lib->Get(ID_SOPHIA_MISSILE_TAIL_LEFT);
	tailUp = lib->Get(ID_SOPHIA_MISSILE_TAIL_UP);
	tailRight = lib->Get(ID_SOPHIA_MISSILE_TAIL_RIGHT);
	tailDown = lib->Get(ID_SOPHIA_MISSILE_TAIL_DOWN);

	direction.Set(dir_x, dir_y);
	SetSprites();
	velocity.Set(MISSILE_SPEED * dir_x, MISSILE_SPEED * dir_y);

	head->GetSize(headWidth, headHeight);
	tail->GetSize(tailWidth, tailHeight);

	collisionBox = new CDynamicBox(
		this,
		-headWidth / 2, -headHeight / 2,
		headWidth, headHeight
	);
	collisionBox->SetSolid(false);
}

void CMissile::Update(DWORD dt)
{
	searcher->Follow(position.x, position.y);

	switch (state)
	{
	case MISSILE_CHASE:
		ChaseState(dt);
		break;
	case MISSILE_SEARCH:
		SearchState(dt);
		break;
	default:
		break;
	}

	position.Set(position.x + direction.x * MISSILE_SPEED, position.y + direction.y * MISSILE_SPEED);
	collisionBox->Update();

	SetSprites();

	countUp += dt;
	bool delete_condition = countUp >= waitTime;

	velocity.Set(0, 0);
	Move(dt);

	if (IsCollidedWith(GOTYPES::Enemy))
	{
		std::list<LPGameObject> ls;
		GetCollidedWith(GOTYPES::Enemy, ls);

		dynamic_cast<LPEnemy>(ls.front())->InflictDamage(MISSILE_DAMAGE);

		delete_condition = true;
	}

	if (delete_condition)
	{
		SelfDestroy();
		CreateEffect(velocity.x, velocity.y);
	}
}

void CMissile::Render()
{
	head->Draw(position.x - headWidth / 2, position.y - headHeight / 2);
	tail->Draw(
		position.x - headWidth / 2 + tailPos->x, 
		position.y - headHeight / 2 + +tailPos->y
	);
	collisionBox->Render();
}

void CMissile::SearchState(DWORD dt)
{
	if (target != NULL)
	{
		state = MISSILE_CHASE;
		return;
	}
	
	std::list<LPEntity> ls = searcher->GetTargets();

	if (ls.size() != 0)
	{
		target = ls.front();
		state = MISSILE_CHASE;
	}
}

void CMissile::ChaseState(DWORD dt)
{
	if (target == NULL)
	{
		state = MISSILE_SEARCH;
		return;
	}

	if (target->GetId() < 0)
	{
		target = NULL;
		state = MISSILE_SEARCH;
		return;
	}


	Vector distance;
	Vector tCenter = target->GetCenter();

	distance.Set(
		abs(tCenter.x - position.x),
		abs(tCenter.y - position.y)
	);

	if (distance.x > distance.y * 2)
	{
		direction.x = tCenter.x > position.x ? 1 : -1;
		direction.y = 0;
	}
	else if (distance.y > distance.x * 2)
	{
		direction.y = tCenter.y > position.y ? 1 : -1;
		direction.x = 0;
	}
}

void CMissile::SetSprites()
{
	if (direction.x > 0)
	{
		tail = tailRight;
		head = headRight;
		tailPos = &tailPosRight;
	}
	else if (direction.x < 0)
	{
		tail = tailLeft;
		head = headLeft;
		tailPos = &tailPosLeft;
	}
	else if (direction.y > 0)
	{
		tail = tailDown;
		head = headDown;
		tailPos = &tailPosDown;
	}
	else if (direction.y < 0)
	{
		tail = tailUp;
		head = headUp;
		tailPos = &tailPosUp;
	}
}

void CMissile::CreateEffect(float vx, float vy)
{
	float size_x, size_y, dir_x, dir_y, pos_x, pos_y;

	Vector pos = GetCenter();
	Vector size = collisionBox->GetSize();

	pos_x = pos.x;
	pos_y = pos.y;

	size_x = size.x;
	size_y = size.y;

	if (vx == 0) dir_x = 0;
	if (vx > 0) dir_x = 1;
	if (vx < 0) dir_x = -1;

	if (vy == 0) dir_y = 0;
	if (vy > 0) dir_y = 1;
	if (vy < 0) dir_y = -1;

	CExplosion::CreateExplosion(
		pos_x + dir_x * size_x / 2,
		pos_y + dir_y * size_y / 2,
		EXPLOSION_TYPES::Medium
	);
}

void CMissile::SelfDestroy()
{
	LPSceneRequest request = new CSceneRequest(SCENE_REQUEST_TYPES::DeleteEntity);
	request->id = this->id;
	CSceneRequest::AddRequest(request);

	LPSceneRequest req = new CSceneRequest(SCENE_REQUEST_TYPES::DeleteEntity);
	req->id = searcher->GetId();
	CSceneRequest::AddRequest(req);
}
