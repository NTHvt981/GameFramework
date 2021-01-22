#include "SoundLibrary.h"

CSoundLibrary* CSoundLibrary::__instance = NULL;

CSoundLibrary* CSoundLibrary::GetInstance()
{
	if (__instance == NULL) __instance = new CSoundLibrary();
	return __instance;
}

void CSoundLibrary::LoadResources()
{
	themeSound = Sound::LoadSound(MUSIC_PATH);

	playerDeathSound = Sound::LoadSound(PLAYER_DEATH_PATH);
	playerShootSound = Sound::LoadSound(PLAYER_SHOOT_PATH);
	playerJumpSound = Sound::LoadSound(PLAYER_JUMP_PATH);
	playerFireMissileSound = Sound::LoadSound(PLAYER_FIRE_MISSILE_PATH);

}

void CSoundLibrary::LoopMusic()
{
	Sound::Loop(themeSound);
}

void CSoundLibrary::StopMusic()
{
	Sound::Stop(themeSound);
}

void CSoundLibrary::PlayPlayerDeathSound()
{
	Sound::Play(playerDeathSound);
}

void CSoundLibrary::PlayPlayerJumpSound()
{
	Sound::Play(playerJumpSound);
}

void CSoundLibrary::PlayPlayerShootSound()
{
	Sound::Play(playerShootSound);
}

void CSoundLibrary::PlayPlayerFireMissileSound()
{
	Sound::Play(playerFireMissileSound);
}

