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
#define CAMERA_WIDTH 256
#define CAMERA_HEIGHT 256
#define CAMERA_SCALE 2

//width and height when shown
//#define WINDOW_WIDTH 640
//#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 480

//width and height of the whole level
//#define GAME_WIDTH 2048
//#define GAME_HEIGHT 2048
#define GAME_WIDTH 3072
#define GAME_HEIGHT 3072

//#define GRID_WIDTH 64
//#define GRID_HEIGHT 64
#define GRID_WIDTH 128
#define GRID_HEIGHT 128

//#define MAX_FRAME_RATE 120
#define MAX_FRAME_RATE 60

#define ENEMIES_TEXTURE_PATH L"./Resources/Texture/enemies.png"
#define PLAYER_TEXTURE_PATH L"Resources/Texture/PlayerSheetTransparent.png"
#define PLAYER_HEALTH_TEXTURE_PATH L"Resources/Texture/Player health.png"
#define OTHER_OBJECTS_TEXTURE_PATH L"Resources/Texture/OtherObjects.png"
#define BLACK_SCREEN_TEXTURE_PATH L"Resources/Texture/BlackScreen.png"
#define BOSS_TEXTURE_PATH L"Resources/Texture/Boss.png"
#define OPENING_TEXTURE_PATH L"Resources/Texture/Opening.png"
#define ROLLOUT_TEXTURE_PATH L"Resources/Texture/RollOut.png"
#define ITEMS_TEXTURE_PATH L"Resources/Texture/Items.png"

#define TEX_BBOX_PATH L"./Resources/Texture/bbox.png"
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
#define ID_SOPHIA_GUN_LEFT 1000
#define ID_SOPHIA_GUN_RIGHT 1002
#define ID_SOPHIA_GUN_UPLEFT 1001
#define ID_SOPHIA_GUN_UPRIGHT 1003
#define ID_SOPHIA_GUN_UP 1004

#define ID_SOPHIA_HEAD_LEFT 1005
#define ID_SOPHIA_HEAD_RIGHT 1006
#define ID_SOPHIA_HEAD_UPLEFT 1007
#define ID_SOPHIA_HEAD_UPRIGHT 1008

#define ID_SOPHIA_BODY 1009
#define ID_SOPHIA_BODY_UPRIGHT 1010
#define ID_SOPHIA_BODY_UPLEFT 1011

#define ID_SOPHIA_HEAD_EJECT_JASON_LEFT_1 1012
#define ID_SOPHIA_HEAD_EJECT_JASON_LEFT_2 1013
#define ID_SOPHIA_HEAD_EJECT_JASON_RIGHT_1 1014
#define ID_SOPHIA_HEAD_EJECT_JASON_RIGHT_2 1015

#pragma region SPRITE WHEN PLAYER IS INVULNERABLE
#define ID_SOPHIA_GUN_LEFT_WHITE 1100
#define ID_SOPHIA_GUN_RIGHT_WHITE 1102
#define ID_SOPHIA_GUN_UPLEFT_WHITE 1101
#define ID_SOPHIA_GUN_UPRIGHT_WHITE 1103
#define ID_SOPHIA_GUN_UP_WHITE 1104

#define ID_SOPHIA_HEAD_LEFT_WHITE 1105
#define ID_SOPHIA_HEAD_RIGHT_WHITE 1106
#define ID_SOPHIA_HEAD_UPLEFT_WHITE 1107
#define ID_SOPHIA_HEAD_UPRIGHT_WHITE 1108

#define ID_SOPHIA_BODY_WHITE 1109
#define ID_SOPHIA_BODY_UPRIGHT_WHITE 1110
#define ID_SOPHIA_BODY_UPLEFT_WHITE 1111
#pragma endregion

#define ID_SOPHIA_WHEEL_1 1021
#define ID_SOPHIA_WHEEL_2 1022
#define ID_SOPHIA_WHEEL_3 1023
#define ID_SOPHIA_WHEEL_4 1024
#define ID_SOPHIA_WHEEL_5 1025
#define ID_SOPHIA_WHEEL_6 1026
#define ID_SOPHIA_WHEEL_7 1027
#define ID_SOPHIA_WHEEL_8 1028

#define ID_SOPHIA_BULLET_LEFT 1030
#define ID_SOPHIA_BULLET_RIGHT 1031
#define ID_SOPHIA_BULLET_UP 1032

#define ID_FIRE_BALL 1018

#define ID_SOPHIA_MISSILE_HEAD_LEFT 1033
#define ID_SOPHIA_MISSILE_HEAD_UP 1034
#define ID_SOPHIA_MISSILE_HEAD_RIGHT 1035
#define ID_SOPHIA_MISSILE_HEAD_DOWN 1036

#define ID_SOPHIA_MISSILE_TAIL_LEFT 1037
#define ID_SOPHIA_MISSILE_TAIL_UP 1038
#define ID_SOPHIA_MISSILE_TAIL_RIGHT 1039
#define ID_SOPHIA_MISSILE_TAIL_DOWN 1040
#pragma endregion

#pragma region Sophia and jason health
#define ID_SOPHIA_HEALTH_BAR 1200
#define ID_JASON_HEALTH_BAR 1201
#define ID_TEXT_POW 1202
#define ID_TEXT_HOV 1203
#pragma endregion

#pragma region Jason texture
#define ID_JASON_WALK_LEFT_1 1301
#define ID_JASON_WALK_LEFT_2 1302
#define ID_JASON_WALK_LEFT_3 1303
#define ID_JASON_WALK_LEFT_4 1304

#define ID_JASON_WALK_RIGHT_1 1305
#define ID_JASON_WALK_RIGHT_2 1306
#define ID_JASON_WALK_RIGHT_3 1307
#define ID_JASON_WALK_RIGHT_4 1308

#define ID_JASON_CLIMB_1 1309
#define ID_JASON_CLIMB_2 1310

#define ID_JASON_CRAWL_LEFT_1 1311
#define ID_JASON_CRAWL_LEFT_2 1312

#define ID_JASON_CRAWL_RIGHT_1 1313
#define ID_JASON_CRAWL_RIGHT_2 1314

#define ID_JASON_FALL_1 1315
#define ID_JASON_FALL_2 1316

#define ID_JASON_BULLET 1317
#pragma endregion

#pragma region Jason topdown texture
#define ID_JASON_TOPDOWN_WALK_DOWN_1 1501
#define ID_JASON_TOPDOWN_WALK_DOWN_2 1502
#define ID_JASON_TOPDOWN_WALK_DOWN_3 1503

#define ID_JASON_TOPDOWN_WALK_LEFT_1 1504
#define ID_JASON_TOPDOWN_WALK_LEFT_2 1505
#define ID_JASON_TOPDOWN_WALK_LEFT_3 1506

#define ID_JASON_TOPDOWN_WALK_UP_1 1507
#define ID_JASON_TOPDOWN_WALK_UP_2 1508
#define ID_JASON_TOPDOWN_WALK_UP_3 1509

#define ID_JASON_TOPDOWN_WALK_RIGHT_1 1510
#define ID_JASON_TOPDOWN_WALK_RIGHT_2 1511
#define ID_JASON_TOPDOWN_WALK_RIGHT_3 1512

#define ID_JASON_TOPDOWN_BULLET_LEFT 1513
#define ID_JASON_TOPDOWN_BULLET_UP 1514
#define ID_JASON_TOPDOWN_BULLET_RIGHT 1515
#define ID_JASON_TOPDOWN_BULLET_DOWN 1516
#pragma endregion

#pragma region ITEMS
#define ID_PLAYER_UPGRADE 1700
#define ID_HEALTH_BALL 1701
#define ID_ENERGY_BALL 1702
#define ID_POWER_BALL 1703
#pragma endregion

#pragma region EXPLOSION
#define ID_EXPLOSION_1 1704
#define ID_EXPLOSION_2 1705
#define ID_EXPLOSION_3 1706
#define ID_EXPLOSION_4 1707
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

#pragma region ENEMY SKULL
#define ID_SKULL_MOVE_LEFT_1 2115
#define ID_SKULL_MOVE_LEFT_2 2116

#define ID_SKULL_MOVE_RIGHT_1 2117
#define ID_SKULL_MOVE_RIGHT_2 2118
#pragma endregion

#pragma region ENEMY FLOATER
#define ID_FLOATER_MOVE_1 2119
#define ID_FLOATER_MOVE_2 2120
#pragma endregion

#pragma region ENEMY INSECT
#define ID_INSECT_MOVE_LEFT_1 2121
#define ID_INSECT_MOVE_LEFT_2 2122

#define ID_INSECT_MOVE_RIGHT_1 2123
#define ID_INSECT_MOVE_RIGHT_2 2124
#pragma endregion

#pragma region BOSS
#define ID_BOSS_HEAD_1 5001
#define ID_BOSS_HEAD_2 5002
#define ID_BOSS_HEAD_3 5003
#define ID_BOSS_HEAD_4 5004
#define ID_BOSS_HEAD_5 5005
#define ID_BOSS_HEAD_6 5006
#define ID_BOSS_HEAD_7 5007
#define ID_BOSS_HEAD_8 5008

#define ID_BOSS_LEFT_ARM 5009
#define ID_BOSS_LEFT_HAND 5010

#define ID_BOSS_RIGHT_ARM 5011
#define ID_BOSS_RIGHT_HAND 5012
#pragma endregion


#define ID_MINE_BULLET 5998
#define ID_SKULL_BULLET 5999

#define ID_BREAKABLE_WALL 6000
#define ID_PORTAL_FACE_RIGHT_1 6001
#define ID_PORTAL_FACE_RIGHT_2 6002
#define ID_PORTAL_FACE_LEFT_1 6003
#define ID_PORTAL_FACE_LEFT_2 6004

#define ID_BLACK_SCREEN 6005

#define ID_OPENING_1 6011
#define ID_OPENING_2 6012
#define ID_OPENING_3 6013
#define ID_OPENING_4 6014
#define ID_OPENING_5 6015
#define ID_OPENING_6 6016
#define ID_OPENING_7 6017
#define ID_OPENING_8 6018
#define ID_OPENING_9 6019

#define ID_OPENING_10 6020
#define ID_OPENING_11 6021
#define ID_OPENING_12 6022
#define ID_OPENING_13 6023
#define ID_OPENING_14 6024
#define ID_OPENING_15 6025
#define ID_OPENING_16 6026
#define ID_OPENING_17 6027
#define ID_OPENING_18 6028
#define ID_OPENING_19 6029

#define ID_OPENING_20 6030
#define ID_OPENING_21 6031
#define ID_OPENING_22 6032
#define ID_OPENING_23 6033
#define ID_OPENING_24 6034
#define ID_OPENING_25 6035
#define ID_OPENING_26 6036
#define ID_OPENING_27 6037
#define ID_OPENING_28 6038
#define ID_OPENING_29 6039

#define ID_OPENING_30 6040
#define ID_OPENING_31 6041
#define ID_OPENING_32 6042
#define ID_OPENING_33 6043
#define ID_OPENING_34 6044
#define ID_OPENING_35 6045
#define ID_OPENING_36 6046
#define ID_OPENING_37 6047

#define ID_ROLLOUT_1 6101
#define ID_ROLLOUT_2 6102
#define ID_ROLLOUT_3 6103
#define ID_ROLLOUT_4 6104
#define ID_ROLLOUT_5 6105
#define ID_ROLLOUT_6 6106
#define ID_ROLLOUT_7 6107
#define ID_ROLLOUT_8 6108
#define ID_ROLLOUT_9 6109
#define ID_ROLLOUT_10 6110
//enum class GOTYPES;

class CScene;
typedef CScene* LPScene;

class CGameRequest;
typedef CGameRequest* LPGameRequest;

class CSceneRequest;
typedef CSceneRequest* LPSceneRequest;

class CGameObject;
typedef CGameObject* LPGameObject;

class CEntity;
typedef CEntity* LPEntity;

class CEnemy;
typedef CEnemy* LPEnemy;

class CPlayer;
typedef CPlayer* LPPlayer;

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

#define SIDESCROLL_LEVEL_SIZE Vector(3072, 3072)
#define TOPDOWN_LEVEL_SIZE Vector(2048, 2048)

#define INTRO_TO_SIDESCROLL_POS Vector(200, 2944)
#define SIDESCROLL_TO_TOPDOWN_POS Vector(128, 1888)

#define TOPDOWN_TO_SIDESCROLL_POS Vector(2400, 400)
#define TOPDOWN_TO_BOSS_POS Vector(128, 192)
