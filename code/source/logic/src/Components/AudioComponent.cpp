#include "Logic/Components/AudioComponent.h"
#include "AudioSystem/API/IAudioAPI.h"

namespace logic
{

AudioComponent::AudioComponent(std::shared_ptr<audios::IAudioAPI> i_audioAPI)
	: m_audioAPI(*i_audioAPI.get())
{
}

} // namespace logic