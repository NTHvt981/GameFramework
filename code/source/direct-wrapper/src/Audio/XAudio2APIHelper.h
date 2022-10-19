#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

namespace audios
{

HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);

HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset);

} // namespace audios