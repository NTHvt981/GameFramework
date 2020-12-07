#pragma once

#include "../Constraints.h"
#include "../GameObject/Entity.h"
#include <map>
#include "../FileAndString/ReadTileSet.h"

#include "..\GameObject\StaticObjects\AntiPlayer.h"
#include "../AreaAndScene/Area.h"

using namespace std;

#define NORMAL_MODE 0
#define BEGIN_CHANGEAREA_MODE 1
#define DURING_CHANGEAREA_MODE 2
#define END_CHANGEAREA_MODE 3

enum class SCENE_TYPES
{
	IntroScene,
	SideScrollScene,
	TopDownScene,
	EndingScene
};

class CScene
{
protected:
	map<int, LPEntity> mapEntities = map<int, LPEntity>();

public:
	SCENE_TYPES Type;

	virtual void LoadResources() {};
	virtual void Update(DWORD dt) {};
	virtual void Render() {};
	virtual void End() {};

	LPEntity GetEntity(int id);
};

void LoadFileParam(
	int& tile_count, int& tile_width, int& tile_height,
	int& tile_count_width, int& tile_count_height,
	vector<int>& solid_tiles, vector<int>& anti_player_tiles,
	vector<vector<int>>& matrix,
	wstring& tileSetDir, string fileDir = "Resources/Textfile/TileMaTrix.txt"
);

/// <summary>
/// base on camera l, t, r, b get x and y range of grid
/// </summary>
void GetGridXandY(
	int& startX, int& startY, int& endX, int& endY,
	float left, float top, float right, float bottom,
	float gridWidth, float gridHeight,
	int grid_count_width, int grid_count_height);