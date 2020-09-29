#include "TextureLibrary.h"

CTextureLibrary* CTextureLibrary::__instance = NULL;

CTextureLibrary* CTextureLibrary::GetInstance()
{
	if (__instance == NULL) __instance = new CTextureLibrary();
	return __instance;
}

void CTextureLibrary::Add(int id, LPCWSTR filePath)
{
	LPDIRECT3DTEXTURE9 texture = CGraphic::Instance->LoadTexture(filePath);
	textures[id] = texture;
}

void CTextureLibrary::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	LPDIRECT3DTEXTURE9 texture = CGraphic::Instance->LoadTexture(filePath);
	textures[id] = texture;
}

LPDIRECT3DTEXTURE9 CTextureLibrary::Get(unsigned int id)
{
	return textures[id];
}
