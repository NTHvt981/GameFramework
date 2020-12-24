#pragma once

#include "../Constraints.h"
#include "Scene.h"
#include "../Unit/Animation.h"
#include "../Unit/Sprite.h"

#include "../Library/SpriteLibrary.h"

#include "../Game/GameRequest.h"

#include "../Camera/Camera.h"

class CEndingScene: public CScene
{
private:
	LPAnimation animation;
public:
	CEndingScene();
	void LoadResources();
	void Start();
	void Update(DWORD dt);
	void Render();
	void End();
};

