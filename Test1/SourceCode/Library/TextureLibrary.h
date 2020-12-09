#pragma once
#include "../Constraints.h"
#include "../Graphic/Graphic.h"
#include <unordered_map>

#define PLAYER_TEXTURE 1
#define ENEMIES_TEXTURE 2
#define PLAYER_HEALTH_TEXTURE 3
#define OTHER_OBJECTS_TEXTURE 4
#define BLACK_SCREEN_TEXTURE 5
#define BOSS_TEXTURE 6

using namespace std;

class CTextureLibrary
{
private:
	static CTextureLibrary *__instance;

	unordered_map<int, LPDIRECT3DTEXTURE9> textures;
public:
	static CTextureLibrary* GetInstance();

	void Add(int id, LPCWSTR filePath);
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 Get(unsigned int id);
};

