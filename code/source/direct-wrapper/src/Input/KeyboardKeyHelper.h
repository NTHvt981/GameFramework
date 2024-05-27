#pragma once
#include <stdint.h>
#include "Core/DataTypes/KeyboardKey.h"

namespace logic
{

uint64_t ToDirectKeyboardKey(const core::KeyboardKey i_keyboardKey);
core::KeyboardKey ToKeyboardKey(const uint64_t i_directKey);

} // namespace logic
