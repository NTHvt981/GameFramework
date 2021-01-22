#pragma once

#define MUSIC_PATH "Resources/Sound/SoundTrack.wav"

#define PLAYER_DEATH_PATH "Resources/Sound/Blaster Master SFX (33).wav"
#define PLAYER_SHOOT_PATH "Resources/Sound/Blaster Master SFX (6).wav"
#define PLAYER_FIRE_MISSILE_PATH "Resources/Sound/Blaster Master SFX (17).wav"
#define PLAYER_JUMP_PATH "Resources/Sound/Blaster Master SFX (10).wav"

#define ENEMY_SHOOT_PATH ""
#define ENEMY_DEATH_PATH ""

#define BOSS_DEATH_PATH ""
#define BOSS_SHOOT_PATH ""
#define EXPLOSION_PATH ""

#include "Sound.h"

class CSoundLibrary
{
private:
	CSound* themeSound = NULL;

	CSound* playerDeathSound = NULL;
	CSound* playerShootSound = NULL;
	CSound* playerJumpSound = NULL;
	CSound* playerFireMissileSound = NULL;

	CSound* enemyDeathSound = NULL;
	CSound* enemyShootSound = NULL;

	CSound* bossDeathSound = NULL;
	CSound* bossShootSound = NULL;

private:
	static CSoundLibrary* __instance;
public:
	static CSoundLibrary* GetInstance();

public:
	void LoadResources();

	void LoopMusic();
	void StopMusic();

	void PlayPlayerDeathSound();
	void PlayPlayerJumpSound();
	void PlayPlayerShootSound();
	void PlayPlayerFireMissileSound();
};

