#include "InputDebug/DebugInputAPI.h"
#include "Core/DataTypes/Flag.h"

namespace input
{

core::Flag s_initFlag;
core::Flag s_shutdownFlag;

void DebugInputAPI::Initialize()
{
}

void DebugInputAPI::UpdateInput()
{
}

void DebugInputAPI::Pause()
{
}

void DebugInputAPI::Resume()
{
}

void DebugInputAPI::ShutDown()
{
}

bool DebugInputAPI::IsKeyDown(const KeyboardKey i_key)
{
    return false;
}

bool DebugInputAPI::IsKeyUp(const KeyboardKey i_key)
{
    return false;
}

bool DebugInputAPI::IsKeyPressed(const KeyboardKey i_key)
{
    return false;
}

bool DebugInputAPI::IsKeyRelease(const KeyboardKey i_key)
{
    return false;
}

bool DebugInputAPI::IsKeyHold(const KeyboardKey i_key)
{
    return false;
}

} // namespace graphics
