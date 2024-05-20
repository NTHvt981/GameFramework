#pragma once
#include "Logic/Scenes/IScene.h"

namespace logic
{

struct Mail {};

struct PushSceneMail : Mail
{
	ESceneType Type;
};

struct PopSceneMail : Mail
{

};

} // namespace logic