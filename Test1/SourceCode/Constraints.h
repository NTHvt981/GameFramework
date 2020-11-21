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
#include "./Timer/Timer.h"

#define WINDOW_CLASS_NAME L"NGUYEN TRUNG HIEU'S WINDOW"
#define WINDOW_TITLE L"Test 1"
#define WINDOW_ICON_PATH L".\Resources\Texture\brick.ico" 
#define D3DCOLOR_WHITE D3DCOLOR_XRGB(255, 255, 255)

#define FULLSCREEN true

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
//width and height of the camera
#define CAMERA_WIDTH 320
#define CAMERA_HEIGHT 240

//width and height when shown
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

//width and height of the whole level
//#define GAME_WIDTH 2048
//#define GAME_HEIGHT 2048
#define GAME_WIDTH 3072
#define GAME_HEIGHT 3072

#define GRID_WIDTH 64
#define GRID_HEIGHT 64

//#define MAX_FRAME_RATE 120
#define MAX_FRAME_RATE 90

#define TEX_BRICK_PATH L"./Resources/Texture/brick.png"
#define STEEL_ROBOT_TEXTURE_PATH L"./Resources/Texture/steel robot.png"
#define ENEMIES_TEXTURE_PATH L"./Resources/Texture/enemies.png"
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
#pragma region TANK
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
#define ID_CAR_BODY_UPRIGHT 1019
#define ID_CAR_BODY_UPLEFT 1020

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

#pragma region ENEMY WORM
#define ID_WORM_MOVE_LEFT_1 2000
#define ID_WORM_MOVE_LEFT_2 2001
#define ID_WORM_MOVE_RIGHT_1 2002
#define ID_WORM_MOVE_RIGHT_2 2003
#pragma endregion

#pragma region ENEMY DOME
#define ID_DOME_UP_MOVE_LEFT_1 2004
#define ID_DOME_UP_MOVE_LEFT_2 2005
#define ID_DOME_UP_MOVE_RIGHT_1 2006
#define ID_DOME_UP_MOVE_RIGHT_2 2007

#define ID_DOME_DOWN_MOVE_LEFT_1 2008
#define ID_DOME_DOWN_MOVE_LEFT_2 2009
#define ID_DOME_DOWN_MOVE_RIGHT_1 2010
#define ID_DOME_DOWN_MOVE_RIGHT_2 2011

#define ID_DOME_LEFT_MOVE_UP_1 20012
#define ID_DOME_LEFT_MOVE_UP_2 2013
#define ID_DOME_LEFT_MOVE_DOWN_1 2014
#define ID_DOME_LEFT_MOVE_DOWN_2 2015

#define ID_DOME_RIGHT_MOVE_UP_1 2016
#define ID_DOME_RIGHT_MOVE_UP_2 2017
#define ID_DOME_RIGHT_MOVE_DOWN_1 2018
#define ID_DOME_RIGHT_MOVE_DOWN_2 2019
#pragma endregion

#pragma region ENEMY JUMPER
#define ID_JUMPER_MOVE_LEFT_1 2100
#define ID_JUMPER_MOVE_LEFT_2 2101
#define ID_JUMPER_MOVE_LEFT_3 2102

#define ID_JUMPER_MOVE_RIGHT_1 2103
#define ID_JUMPER_MOVE_RIGHT_2 2104
#define ID_JUMPER_MOVE_RIGHT_3 2105
#pragma endregion

#pragma region ENEMY ORB
#define ID_ORB_1 2106
#define ID_ORB_2 2107
#define ID_ORB_3 2108
#define ID_ORB_4 2109
#define ID_ORB_5 2110
#pragma endregion

#pragma region ENEMY WALKER
#define ID_WALKER_1 2111
#define ID_WALKER_2 2112
#define ID_WALKER_3 2113
#define ID_WALKER_4 2114
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

class CGrid;