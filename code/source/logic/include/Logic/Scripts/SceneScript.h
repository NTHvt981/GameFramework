#pragma once
#include "Script.h"
#include "Core/Signals/Callback.h"
#include <optional>

namespace logic
{

class SceneScript : public Script
{
public:
	signals::Callback<std::unique_ptr<SceneScript>> requestAddSceneCallback;
	signals::Callback<std::unique_ptr<SceneScript>> requestReplaceSceneCallback;
};

} // namespace logic