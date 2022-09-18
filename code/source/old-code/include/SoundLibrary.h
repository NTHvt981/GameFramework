#pragma once

#define MUSIC_PATH "Resources/Sound/SoundTrack.wav"

#define PLAYER_DEATH_PATH "Resources/Sound/Blaster Master SFX (34).wav"
#define PLAYER_HURT_PATH "Resources/Sound/Blaster Master SFX (19).wav"
#define PLAYER_SHOOT_PATH "Resources/Sound/Blaster Master SFX (6).wav"
#define PLAYER_FIRE_MISSILE_PATH "Resources/Sound/Blaster Master SFX (17).wav"
#define PLAYER_JUMP_PATH "Resources/Sound/Blaster Master SFX (10).wav"
#define PLAYER_TOUCH_GROUND_PATH "Resources/Sound/Blaster Master SFX (7).wav"

#define ENEMY_SHOOT_PATH "Resources/Sound/Blaster Master SFX (6).wav"
#define ENEMY_DEATH_PATH "Resources/Sound/Blaster Master SFX (25).wav"

#define BOSS_DEATH_PATH "Resources/Sound/Blaster Master SFX (35).wav"
#define BOSS_SHOOT_PATH "Resources/Sound/Blaster Master SFX (6).wav"
#define EXPLOSION_PATH "Resources/Sound/Blaster Master SFX (29).wav"

#include "Sound.h"

class CSoundLibrary
{
private:
	CSound* themeSound = NULL;

	CSound* playerDeathSound = NULL;
	CSound* playerShootSound = NULL;
	CSound* playerHurtSound = NULL;
	CSound* playerJumpSound = NULL;
	CSound* playerFireMissileSound = NULL;
	CSound* playerTouchGroundSound = NULL;

	CSound* enemyDeathSound = NULL;
	CSound* enemyShootSound = NULL;

	CSound* bossDeathSound = NULL;
	CSound* bossShootSound = NULL;

	CSound* explosionSound = NULL;

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
	void PlayPlayerHurtSound();
	void PlayPlayerShootSound();
	void PlayPlayerFireMissileSound();
	void PlayPlayerTouchGroundSound();

	void PlayEnemyDeathSound();
	void PlayEnemyShootSound();

	void PlayBossDeathSound();
	void PlayBossShootSound();

	void PlayExplosionSound();
};

