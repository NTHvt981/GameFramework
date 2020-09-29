#pragma once
#include "../Constraints.h"
#include "../Graphic/Graphic.h"
#include <unordered_map>

#define CAR_TEXTURE 1

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

