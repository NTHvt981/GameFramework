#pragma once

#include "Constraints.h"
#include "Scene.h"
#include "Animation.h"
#include "Sprite.h"

#include "SpriteLibrary.h"

#include "GameRequest.h"

#include "Camera.h"

#include "Sound.h"

class CIntroScene: public CScene
{
private:
	LPAnimation animation;
public:
	CIntroScene();
	void LoadResources();
	void Start();
	void Update(DWORD dt);
	void Render();
	void End();
};

