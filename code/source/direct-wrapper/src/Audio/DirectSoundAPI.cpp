#include "DirectWrapper/Audio/DirectSoundAPI.h"
#include "Core/Macros/Macros.h"
#include "wave_file.h"
#include <assert.h>
#include <mmsystem.h>
#include <Windows.h>
#include <mmreg.h>
#include <dsound.h>
#include <DxErr.h>
#include <assert.h>
#include <dinput.h>

namespace audios
{

DirectSoundAPI::DirectSoundAPI(const HWND i_hwnd)
	: m_hwnd(i_hwnd)
{
}

void DirectSoundAPI::Initialize()
{
    HRESULT result = DirectSoundCreate8(NULL, &m_directSound, NULL);
    DEBUG(assert(SUCCEEDED(result)));

    result = m_directSound->SetCooperativeLevel(m_hwnd, DSSCL_PRIORITY);
    DEBUG(assert(SUCCEEDED(result)));

    DSBUFFERDESC bufferDescription;
    ZeroMemory(&bufferDescription, sizeof(DSBUFFERDESC));
    bufferDescription.dwSize = sizeof(DSBUFFERDESC);
    bufferDescription.dwFlags = DSBCAPS_PRIMARYBUFFER;
    bufferDescription.dwBufferBytes = 0;
    bufferDescription.lpwfxFormat = NULL;

    result = m_directSound->CreateSoundBuffer(
        &bufferDescription,
        &m_primarySoundBuffer,
        NULL
    );
    DEBUG(assert(SUCCEEDED(result)));

    WAVEFORMATEX waveFormat;
    ZeroMemory(&waveFormat, sizeof(WAVEFORMATEX));
    waveFormat.wFormatTag = (WORD) WAVE_FORMAT_PCM;
    waveFormat.nChannels = (WORD) 2;
    waveFormat.nSamplesPerSec = (DWORD) 8000; //8.0 kHz, 11.025 kHz, 22.05 kHz, or 44.1 kHz
    waveFormat.wBitsPerSample = (WORD) 16;
    waveFormat.nBlockAlign = (WORD)(waveFormat.wBitsPerSample / 8 * waveFormat.nChannels);
    waveFormat.nAvgBytesPerSec = (DWORD)(waveFormat.nSamplesPerSec * waveFormat.nBlockAlign);
    result = m_primarySoundBuffer->SetFormat(&waveFormat);
    DEBUG(assert(SUCCEEDED(result)));
}

void DirectSoundAPI::LoadSound(const core::SoundId i_soundId, const core::String& i_textureFilePath)
{
    wav_file waveFileData;
    std::string stdString = i_textureFilePath.ToStdStr();
    readWaveData(stdString.c_str(), &waveFileData);
    printWaveData(&waveFileData);

    WAVEFORMATEX formatEx;
    ZeroMemory(&formatEx, sizeof(WAVEFORMATEX));
    formatEx.cbSize = waveFileData.cbSize;
    formatEx.wFormatTag = waveFileData.audioFormat;
    formatEx.nChannels = waveFileData.numChannels;
    formatEx.wBitsPerSample = waveFileData.bitsPerSample;
    formatEx.nAvgBytesPerSec = waveFileData.byteRate;
    formatEx.nBlockAlign = waveFileData.blockAlign;
    formatEx.nSamplesPerSec = waveFileData.sampleRate;
    
    DSBUFFERDESC bufferDescription;
    ZeroMemory(&bufferDescription, sizeof(DSBUFFERDESC));
    bufferDescription.dwSize = sizeof(DSBUFFERDESC);
    bufferDescription.dwBufferBytes = waveFileData.chunkSize;
    bufferDescription.dwFlags = DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;
    bufferDescription.lpwfxFormat = &formatEx;
    bufferDescription.dwReserved = 0;
    bufferDescription.guid3DAlgorithm = DS3DALG_DEFAULT;

    LPDIRECTSOUNDBUFFER soundBuffer = nullptr;
    HRESULT createResult = m_directSound->CreateSoundBuffer(
        &bufferDescription,
        &soundBuffer,
        NULL // Must be NULL.
    );
    assert(SUCCEEDED(createResult));

    m_mapSoundBuffers[i_soundId] = soundBuffer;
}

void DirectSoundAPI::Play(const core::SoundId i_soundId, const SoundSettings& i_settings)
{
    DWORD status;
    HRESULT getStatusResult = m_primarySoundBuffer->GetStatus(&status);
    assert(SUCCEEDED(getStatusResult));

    assert(status != DSBSTATUS_BUFFERLOST);
    
    assert(m_mapSoundBuffers.contains(i_soundId));
    LPDIRECTSOUNDBUFFER bufferToPlay = m_mapSoundBuffers[i_soundId];

    HRESULT result = bufferToPlay->SetCurrentPosition(0);
    result = bufferToPlay->SetVolume(-i_settings.volume);
    assert(SUCCEEDED(result));
    result = bufferToPlay->SetFrequency(i_settings.frequency);
    assert(SUCCEEDED(result));
    result = bufferToPlay->SetPan(i_settings.pan);
    assert(SUCCEEDED(result));
    DWORD playFlag = 0;
    playFlag = i_settings.loop ? playFlag | DSBPLAY_LOOPING : playFlag;

    result = bufferToPlay->Play(0, 0, playFlag);
    assert(SUCCEEDED(result));
}

void DirectSoundAPI::Pause()
{

}

void DirectSoundAPI::Resume()
{
}

void DirectSoundAPI::Shutdown()
{
    for (auto& [id, buffer] : m_mapSoundBuffers)
    {
        buffer->Release();
    }

    m_primarySoundBuffer->Release();
    m_directSound->Release();
}

} // namespace audios