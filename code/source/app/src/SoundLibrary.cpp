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
	playerHurtSound = Sound::LoadSound(PLAYER_HURT_PATH);
	playerTouchGroundSound = Sound::LoadSound(PLAYER_TOUCH_GROUND_PATH);

	enemyDeathSound = Sound::LoadSound(ENEMY_DEATH_PATH);
	enemyShootSound = Sound::LoadSound(ENEMY_SHOOT_PATH);

	bossDeathSound = Sound::LoadSound(BOSS_DEATH_PATH);
	bossShootSound = Sound::LoadSound(BOSS_SHOOT_PATH);

	explosionSound = Sound::LoadSound(EXPLOSION_PATH);
}

void CSoundLibrary::LoopMusic()
{
	Sound::Loop(themeSound);
}

void CSoundLibrary::StopMusic()
{
	Sound::Stop(themeSound);
	themeSound->Reset();
}

void CSoundLibrary::PlayPlayerDeathSound()
{
	Sound::PlayFromBegin(playerDeathSound);
}

void CSoundLibrary::PlayPlayerJumpSound()
{
	Sound::PlayFromBegin(playerJumpSound);
}

void CSoundLibrary::PlayPlayerHurtSound()
{
	Sound::PlayFromBegin(playerHurtSound);
}

void CSoundLibrary::PlayPlayerShootSound()
{
	Sound::PlayFromBegin(playerShootSound);
}

void CSoundLibrary::PlayPlayerFireMissileSound()
{
	Sound::PlayFromBegin(playerFireMissileSound);
}

void CSoundLibrary::PlayPlayerTouchGroundSound()
{
	Sound::PlayFromBegin(playerTouchGroundSound);
}

void CSoundLibrary::PlayEnemyDeathSound()
{
	Sound::PlayFromBegin(enemyDeathSound);
}

void CSoundLibrary::PlayEnemyShootSound()
{
	Sound::PlayFromBegin(enemyShootSound);
}

void CSoundLibrary::PlayBossDeathSound()
{
	Sound::PlayFromBegin(bossDeathSound);
}

void CSoundLibrary::PlayBossShootSound()
{
	Sound::PlayFromBegin(bossShootSound);
}

void CSoundLibrary::PlayExplosionSound()
{
	//Sound::PlayFromBegin(explosionSound);
}

