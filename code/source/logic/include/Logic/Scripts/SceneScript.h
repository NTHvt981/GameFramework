#pragma once
#include "Script.h"
#include "Core/Signals/Signal.h"
#include <optional>

namespace logic
{

class SceneScript : public Script
{
public:
	signals::Signal<std::unique_ptr<SceneScript>> sig_requestAddScene;
	signals::Connection<std::unique_ptr<SceneScript>> requestAddSceneCon;
};

} // namespace logic