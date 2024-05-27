#pragma once
#include "Core/DataTypes/KeyboardKey.h"
#include <stdint.h>

namespace core
{

class INativeInputAPI
{
public:
	virtual void Initialize() = 0;
	virtual void UpdateInput() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Shutdown() = 0;

	virtual bool IsKeyDown(const core::KeyboardKey i_key) = 0; // when press of hold key
	virtual bool IsKeyUp(const core::KeyboardKey i_key) = 0; // oposite of IsKeyDown
	virtual bool IsKeyPressed(const core::KeyboardKey i_key) = 0; // when just press key
	virtual bool IsKeyRelease(const core::KeyboardKey i_key) = 0; // when just release key
	virtual bool IsKeyHold(const core::KeyboardKey i_key) = 0;
};

} // namespace core
