#pragma once
#include "SceneScript.h"

namespace logic
{

class SideScrollSceneScript : public SceneScript
{
public:
	void OnCreate(std::shared_ptr<IScriptContext> i_scriptContext) override;
	void OnDestroy() override;
};

} // namespace logic