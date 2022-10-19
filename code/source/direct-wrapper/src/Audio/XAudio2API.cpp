#include "DirectWrapper/Audio/XAudio2API.h"
#include "XAudio2APIHelper.h"
#include "Core/Macros/Macros.h"
#include <assert.h>
#include <combaseapi.h>

namespace audios
{

XAudio2API::XAudio2API()
{
}

void XAudio2API::Initialize()
{
	HRESULT result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(result));

	result = XAudio2Create(&m_xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	assert(SUCCEEDED(result));

	result = m_xAudio2->CreateMasteringVoice(&m_masterVoice);
	assert(SUCCEEDED(result));
}

void XAudio2API::LoadSound(const core::SoundId i_soundId, const core::String& i_textureFilePath)
{
	std::wstring stdWString = i_textureFilePath.ToStdWStr();
	HANDLE fileHandle = CreateFile(
		stdWString.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	assert(fileHandle != INVALID_HANDLE_VALUE);
	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		auto errorCode = HRESULT_FROM_WIN32(GetLastError());
		throw(errorCode);
	}

	DWORD filePointer = SetFilePointer(fileHandle, 0, NULL, FILE_BEGIN);
	assert(filePointer != INVALID_SET_FILE_POINTER);
	if (filePointer == INVALID_SET_FILE_POINTER)
	{
		auto errorCode = HRESULT_FROM_WIN32(GetLastError());
		throw(errorCode);
	}

	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	//check the file type, should be fourccWAVE or 'XWMA'
	HRESULT result = FindChunk(fileHandle, 'FFIR', dwChunkSize, dwChunkPosition);
	assert(SUCCEEDED(result));

	DWORD filetype;
	result = ReadChunkData(fileHandle, &filetype, sizeof(DWORD), dwChunkPosition);
	assert(SUCCEEDED(result));

	result = FindChunk(fileHandle, ' tmf', dwChunkSize, dwChunkPosition);
	assert(SUCCEEDED(result));

	WAVEFORMATEXTENSIBLE wfx = { 0 };
	result = ReadChunkData(fileHandle, &wfx, dwChunkSize, dwChunkPosition);
	assert(SUCCEEDED(result));

	//fill out the audio data buffer with the contents of the fourccDATA chunk
	result = FindChunk(fileHandle, 'atad', dwChunkSize, dwChunkPosition);
	assert(SUCCEEDED(result));

	BYTE* pDataBuffer = new BYTE[dwChunkSize];
	result = ReadChunkData(fileHandle, pDataBuffer, dwChunkSize, dwChunkPosition);
	assert(SUCCEEDED(result));

	XAUDIO2_BUFFER buffer = { 0 };
	buffer.AudioBytes = dwChunkSize;  //size of the audio buffer in bytes
	buffer.pAudioData = pDataBuffer;  //buffer containing audio data
	buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer

	IXAudio2SourceVoice* pSourceVoice;
	result = m_xAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&wfx);
	assert(SUCCEEDED(result));

	result = pSourceVoice->SubmitSourceBuffer(&buffer);
	assert(SUCCEEDED(result));

	m_mapSourceVoices[i_soundId] = pSourceVoice;
}

void XAudio2API::Play(const core::SoundId i_soundId, const SoundSettings& i_settings)
{
	HRESULT result = m_mapSourceVoices[i_soundId]->Start(0);
	assert(SUCCEEDED(result));
}

void XAudio2API::Pause()
{

}

void XAudio2API::Resume()
{
}

void XAudio2API::Shutdown()
{
}

} // namespace audios