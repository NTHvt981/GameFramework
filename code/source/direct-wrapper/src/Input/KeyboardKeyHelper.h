#pragma once
#include <stdint.h>

namespace inputs
{

enum class KeyboardKey: uint64_t;

uint64_t ToDirectKeyboardKey(const KeyboardKey i_keyboardKey);
KeyboardKey ToKeyboardKey(const uint64_t i_directKey);

} // namespace inputs
