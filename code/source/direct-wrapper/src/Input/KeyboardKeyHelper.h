#pragma once
#include "InputSystem/DataTypes/KeyboardKey.h"

namespace input
{

uint64_t ToDirectKeyboardKey(const KeyboardKey i_keyboardKey);
KeyboardKey ToKeyboardKey(const uint64_t i_directKey);

} // namespace input
