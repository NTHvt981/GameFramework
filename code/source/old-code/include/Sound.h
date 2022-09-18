#pragma once
#include <iostream>

#include "Audio.h"

class Sound
{
private:
	static CSoundManager* dsound;

	Sound()  // Disallow creating an instance of this object
	{

	}

	~Sound()
	{

	}

public:
	static bool DirectSound_Init(HWND hwnd);
	static void DirectSound_Shutdown();
	static CSound* LoadSound(std::string filename);
	static void Play(CSound* sound);
	static void Loop(CSound* sound);
	static void Stop(CSound* sound);

	static void PlayFromBegin(CSound* sound);
	static void LoopFromBegin(CSound* sound);

};

