#pragma once
#include "Constraints.h"
#include "Graphic.h"
#include <unordered_map>

#define PLAYER_TEXTURE 1
#define ENEMIES_TEXTURE 2
#define PLAYER_HEALTH_TEXTURE 3
#define OTHER_OBJECTS_TEXTURE 4
#define BLACK_SCREEN_TEXTURE 5
#define BOSS_TEXTURE 6
#define OPENING_TEXTURE 7
#define ROLLOUT_TEXTURE 8
#define ITEMS_TEXTURE 9



class CTextureLibrary
{
private:
	static CTextureLibrary *__instance;

	std::unordered_map<int64_t, LPDIRECT3DTEXTURE9> textures;
public:
	static CTextureLibrary* GetInstance();

	void Add(int64_t id, LPCWSTR filePath);
	void Add(int64_t id, LPCWSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 Get(uint64_t id);
};

