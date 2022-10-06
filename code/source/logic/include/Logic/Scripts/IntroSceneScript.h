#pragma once
#include "SceneScript.h"

namespace logic
{

class IntroSceneScript: public SceneScript
{
public:
	void OnCreate(std::shared_ptr<IScriptContext> i_scriptContext) override;
	void OnDestroy() override;
};

} // namespace logic