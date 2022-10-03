#pragma once
#include "InputSystem/DataTypes/KeyboardKey.h"

namespace inputs
{

class IInputAPI
{
public:
	virtual bool IsKeyDown(const KeyboardKey i_key) const = 0; // when press of hold key
	virtual bool IsKeyUp(const KeyboardKey i_key) const = 0; // oposite of IsKeyDown
	virtual bool IsKeyPressed(const KeyboardKey i_key) const = 0; // when just press key
	virtual bool IsKeyRelease(const KeyboardKey i_key) const = 0; // when just release key
	virtual bool IsKeyHold(const KeyboardKey i_key) const = 0;
};

} // namespace inputs
