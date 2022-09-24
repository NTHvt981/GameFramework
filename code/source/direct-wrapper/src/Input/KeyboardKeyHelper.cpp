#include "KeyboardKeyHelper.h"
#include <dinput.h>

namespace input
{

uint64_t ToDirectKeyboardKey(const KeyboardKey i_keyboardKey)
{
	switch (i_keyboardKey)
	{
	case KeyboardKey::Escape:
		return DIK_ESCAPE;
	case KeyboardKey::Space:
		return DIK_SPACE;
	default:
		return DIK_0;
	}
}

KeyboardKey ToKeyboardKey(const uint64_t i_directKey)
{
	switch (i_directKey)
	{
	case DIK_ESCAPE:
		return KeyboardKey::Escape;
	case DIK_SPACE:
		return KeyboardKey::Space;
	default:
		return KeyboardKey::N0;
		break;
	}
}

} // namespace input