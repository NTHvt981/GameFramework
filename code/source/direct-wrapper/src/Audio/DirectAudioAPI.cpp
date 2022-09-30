#include "DirectWrapper/Audio/DirectAudioAPI.h"
#include <mmsystem.h>
#include <mmreg.h>
#include <dsound.h>
#include <DxErr.h>
#include <assert.h>
#include <dinput.h>

namespace audios
{

DirectAudioAPI::DirectAudioAPI(const HWND i_hwnd)
	: m_hwnd(i_hwnd)
{
}

void DirectAudioAPI::Initialize()
{
    HRESULT result = DirectSoundCreate8(NULL, &m_directSound, NULL);
    assert(SUCCEEDED(result));

    result = m_directSound->SetCooperativeLevel(m_hwnd, DISCL_FOREGROUND);
    assert(SUCCEEDED(result));

    DSBUFFERDESC bufferDescription;
    ZeroMemory(&bufferDescription, sizeof(DSBUFFERDESC));
    bufferDescription.dwSize = sizeof(DSBUFFERDESC);
    bufferDescription.dwFlags = DSBCAPS_PRIMARYBUFFER;
    bufferDescription.dwBufferBytes = 0;
    bufferDescription.lpwfxFormat = NULL;

    result = m_directSound->CreateSoundBuffer(
        &bufferDescription,
        &m_directSoundBuffer,
        NULL
    );
    assert(SUCCEEDED(result));

    WAVEFORMATEX waveFormat;
    ZeroMemory(&waveFormat, sizeof(WAVEFORMATEX));
    waveFormat.wFormatTag = (WORD) WAVE_FORMAT_PCM;
    waveFormat.nChannels = (WORD) 2;
    waveFormat.nSamplesPerSec = (DWORD) 8000; //8.0 kHz, 11.025 kHz, 22.05 kHz, or 44.1 kHz
    waveFormat.wBitsPerSample = (WORD) 16;
    waveFormat.nBlockAlign = (WORD)(waveFormat.wBitsPerSample / 8 * waveFormat.nChannels);
    waveFormat.nAvgBytesPerSec = (DWORD)(waveFormat.nSamplesPerSec * waveFormat.nBlockAlign);
    result = m_directSoundBuffer->SetFormat(&waveFormat);
    assert(SUCCEEDED(result));
}

void DirectAudioAPI::Pause()
{
}

void DirectAudioAPI::Resume()
{
}

void DirectAudioAPI::Shutdown()
{
    m_directSound->Release();
    //m_directSoundBuffer->Release();
}

} // namespace audios