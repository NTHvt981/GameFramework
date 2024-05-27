#pragma once
#include "Core/DataTypes/KeyboardKey.h"

namespace core
{

class IInputAPI
{
public:
	virtual bool IsKeyDown(const core::KeyboardKey i_key) const = 0; // when press of hold key
	virtual bool IsKeyUp(const core::KeyboardKey i_key) const = 0; // oposite of IsKeyDown
	virtual bool IsKeyPressed(const core::KeyboardKey i_key) const = 0; // when just press key
	virtual bool IsKeyRelease(const core::KeyboardKey i_key) const = 0; // when just release key
	virtual bool IsKeyHold(const core::KeyboardKey i_key) const = 0;
};

} // namespace core
