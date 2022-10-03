#pragma once
#include "IComponent.h"
#include <stdint.h>
#include <memory>

namespace inputs
{
class IInputAPI;
enum class KeyboardKey : uint64_t;
} // namespace inputs
	
namespace logic
{

static constexpr core::ComponentKey sk_inputComponentKey = "InputComponent";

class InputComponent final : public IComponent
{
public:
	InputComponent(std::weak_ptr<inputs::IInputAPI> i_inputAPI);

	// Inherited via Component
	void Register() override {};
	void Deregister() override {};

	bool IsKeyDown(const inputs::KeyboardKey i_key);
	bool IsKeyUp(const inputs::KeyboardKey i_key);
	bool IsKeyPressed(const inputs::KeyboardKey i_key);
	bool IsKeyRelease(const inputs::KeyboardKey i_key);
	bool IsKeyHold(const inputs::KeyboardKey i_key);

private:
	std::weak_ptr<inputs::IInputAPI> m_inputAPI;
};

} // namespace logic