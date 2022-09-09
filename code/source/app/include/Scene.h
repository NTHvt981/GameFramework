#pragma once

#include "Constraints.h"
#include "Entity.h"
#include <map>
#include "ReadTileSet.h"

#include "AntiPlayer.h"
#include "Area.h"



#define NORMAL_MODE 0
#define BEGIN_CHANGEAREA_MODE 1
#define DURING_CHANGEAREA_MODE 2
#define END_CHANGEAREA_MODE 3

enum class SCENE_TYPES
{
	IntroScene,
	SideScrollScene,
	TopDownScene,
	EndingScene,
	BossScene
};

class CScene
{
protected:
	std::map<int64_t, LPEntity> mapEntities = std::map<int64_t, LPEntity>();

public:
	SCENE_TYPES Type;

	virtual void LoadResources() {};
	virtual void Update(DWORD dt) {};
	virtual void Render() {};
	virtual void End() {};

	LPEntity GetEntity(int64_t id);
};

void LoadFileParam(
	int64_t& tile_count, int64_t& tile_width, int64_t& tile_height,
	int64_t& tile_count_width, int64_t& tile_count_height,
	std::vector<int64_t>& solid_tiles, std::vector<int64_t>& anti_player_tiles,
	std::vector<std::vector<int64_t>>& matrix,
	std::wstring& tileSetDir, std::string fileDir = "Resources/Textfile/TileMaTrix.txt"
);

/// <summary>
/// base on camera l, t, r, b get x and y range of grid
/// </summary>
void GetGridXandY(
	int64_t& startX, int64_t& startY, int64_t& endX, int64_t& endY,
	float left, float top, float right, float bottom,
	float gridWidth, float gridHeight,
	int64_t grid_count_width, int64_t grid_count_height);