#pragma once
#include "IComponent.h"
#include <memory>

namespace audios
{
class IAudioAPI;
} // namespace audios

namespace logic
{

static constexpr core::ComponentKey sk_audioComponentKey = "AudioComponent";

class AudioComponent final : public IComponent
{
public:
	AudioComponent(std::weak_ptr<audios::IAudioAPI> i_audioAPI);

	// Inherited via Component
	void Register() override {};
	void Deregister() override {};

private:
	std::weak_ptr<audios::IAudioAPI> m_audioAPI;
};

} // namespace logic