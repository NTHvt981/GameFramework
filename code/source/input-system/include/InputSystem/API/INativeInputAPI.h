#pragma once
#include <stdint.h>

namespace inputs
{
enum class KeyboardKey : uint64_t;

class INativeInputAPI
{
public:
	virtual void Initialize() = 0;
	virtual void UpdateInput() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Shutdown() = 0;

	virtual bool IsKeyDown(const KeyboardKey i_key) = 0; // when press of hold key
	virtual bool IsKeyUp(const KeyboardKey i_key) = 0; // oposite of IsKeyDown
	virtual bool IsKeyPressed(const KeyboardKey i_key) = 0; // when just press key
	virtual bool IsKeyRelease(const KeyboardKey i_key) = 0; // when just release key
	virtual bool IsKeyHold(const KeyboardKey i_key) = 0;
};

} // namespace inputs
