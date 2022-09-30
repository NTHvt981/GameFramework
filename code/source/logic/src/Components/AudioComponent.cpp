#include "Logic/Components/AudioComponent.h"

namespace logic
{

AudioComponent::AudioComponent(std::weak_ptr<audios::IAudioAPI> i_audioAPI)
	: m_audioAPI(i_audioAPI)
{
}

} // namespace logic