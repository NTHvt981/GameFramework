#pragma once

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <d3dx9core.h>

#include <vector>

#include "./Vector/Vector.h"
#include "./Debug/Debug.h"

#define WINDOW_CLASS_NAME L"NGUYEN TRUNG HIEU'S WINDOW"
#define WINDOW_TITLE L"Test 1"
#define WINDOW_ICON_PATH L".\Resources\Texture\brick.ico" 
#define D3DCOLOR_WHITE D3DCOLOR_XRGB(255, 255, 255)

#define FULLSCREEN false

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

//#define MAX_FRAME_RATE 120
#define MAX_FRAME_RATE 60

#define TEX_BRICK_PATH L"./Resources/Texture/brick.png"
#define STEEL_ROBOT_TEXTURE_PATH L"./Resources/Texture/steel robot.png"
#define TEX_BBOX_PATH L"./Resources/Texture/bbox.png"
#define TEX_CAR_SPRIRESHEET_TRANSPARENT L"Resources/Texture/My car spritesheet transparent.png"
#define ID_TEX_BBOX 999		// special texture to draw object bounding box

#define POSITION_START_X 10
#define POSITION_START_Y 10

//for the states
#define MOVE_LEFT_STATE 0
#define MOVE_RIGHT_STATE 1
#define MOVE_UP_STATE 2
#define MOVE_DOWN_STATE 3

#pragma region TEXTURE PARAMS
#define ID_CAR_GUN_LEFT 1000
#define ID_CAR_GUN_RIGHT 1002
#define ID_CAR_GUN_UPLEFT 1001
#define ID_CAR_GUN_UPRIGHT 1003
#define ID_CAR_GUN_UP 1004

#define ID_CAR_HEAD_LEFT 1005
#define ID_CAR_HEAD_RIGHT 1006
#define ID_CAR_HEAD_UPLEFT 1007
#define ID_CAR_HEAD_UPRIGHT 1008

#define ID_CAR_BODY 1009
#define ID_CAR_WHEEL_1 1010
#define ID_CAR_WHEEL_2 1011
#define ID_CAR_WHEEL_3 1012
#define ID_CAR_WHEEL_4 1013
#define ID_CAR_WHEEL_5 1014
#define ID_CAR_WHEEL_6 1015
#define ID_CAR_WHEEL_7 1016
#define ID_CAR_WHEEL_8 1017

#define ID_FIRE_BALL 1018
#pragma endregion

//enum class GOTYPES;

class CGameObject;
typedef CGameObject* LPGameObject;

class CEntity;
typedef CEntity* LPEntity;

class CCollisionBox;
typedef CCollisionBox* LPCollisionBox;

class CDynamicBox;
typedef CDynamicBox* LPDynamicBox;

class CSprite;
typedef CSprite* LPSprite;

class CAnimationFrame;
typedef CAnimationFrame* LPAnimationFrame;

class CAnimation;
typedef CAnimation* LPAnimation;

class CTileSet;
typedef CTileSet* LPTileSet;

class CTileMap;