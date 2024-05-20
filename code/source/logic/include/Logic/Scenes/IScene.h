#pragma once
#include "Core/DataTypes/Duration.h"

namespace logic
{

enum ESceneType
{
	Intro,
	SideScroll,
	TopDown,
	Outro
};

class IScene
{
public:
	virtual void PreFixedUpdate(const core::Duration& dt) = 0;
	virtual void DuringFixedUpdate(const core::Duration& dt) = 0;
	virtual void PostFixedUpdate(const core::Duration& dt) = 0;

	virtual void PreUpdate(const core::Duration& dt) = 0;
	virtual void DuringUpdate(const core::Duration& dt) = 0;
	virtual void PostUpdate(const core::Duration& dt) = 0;

	virtual void PreRender(const core::Duration& dt) = 0;
	virtual void DuringRender(const core::Duration& dt) = 0;
	virtual void PostRender(const core::Duration& dt) = 0;

	virtual void OnDestroy() = 0;
};

} // namespace logic