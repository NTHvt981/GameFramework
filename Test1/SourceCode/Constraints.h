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

#define BRICK_TEXTURE_PATH L"./Resources/Texture/brick.png"
#define STEEL_ROBOT_TEXTURE_PATH L"./Resources/Texture/steel robot.png"
#define BRICK_START_X 30.0f
#define BRICK_START_Y 10.0f
#define BRICK_START_VX 0.2f
#define BRICK_WIDTH 16.0f

#define POSITION_START_X 10
#define POSITION_START_Y 10

//for the states
#define MOVE_LEFT_STATE 0
#define MOVE_RIGHT_STATE 1
#define MOVE_UP_STATE 2
#define MOVE_DOWN_STATE 3

#pragma region TEXTURE PARAMS
const int CAR_GUN_LEFT[] = { 11,2,	18,	9 };
const int CAR_GUN_UPLEFT[] = { 20,	2,	27,	9 };
const int CAR_GUN_UP[] = { 29,	2,	36,	9 };
const int CAR_GUN_UPRIGHT[] = { 20,	11,	27,	18 };
const int CAR_GUN_RIGHT[] = { 29,	11,	36,	18 };

const int CAR_HEAD_LEFT[] = { 2,	20,	17,	27 };
const int CAR_HEAD_RIGHT[] = { 2,	29,	17,	36 };
const int CAR_HEAD_UPRIGHT[] = { 38,	20,	53,	35 };
const int CAR_HEAD_UPLEFT[] = { 56,	20,	71,	36 };

const int WHEEL_1[] = { 100, 38,	11,	45,	18 };
const int WHEEL_2[] = { 101, 47,	11,	54,	18 };
const int WHEEL_3[] = { 102, 56,	11,	63,	18 };
const int WHEEL_4[] = { 103, 65,	11,	72,	18 };
#pragma endregion

//enum class GOTYPES;

class CGameObject;
typedef CGameObject* LPGameObject;

class CEntity;
typedef CEntity* LPEntity;

class CCollisionBox;
typedef CCollisionBox* LPCollisionBox;

class CSprite;
typedef CSprite* LPSprite;

class CAnimationFrame;
typedef CAnimationFrame* LPAnimationFrame;

class CAnimation;
typedef CAnimation* LPAnimation;