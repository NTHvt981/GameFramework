#include "Game.h"

CGame* CGame::__instance = NULL;

CGame* CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}

void CGame::Init(HINSTANCE hInstance, int64_t nCmdShow, int64_t width, int64_t height, bool fullscreen)
{
	hWnd = CreateGameWindow(hInstance, nCmdShow, width, height);
	CGraphic::Instance->Init(hWnd);

	CInput::GetInstance()->Init(hInstance, hWnd);
	Sound::DirectSound_Init(hWnd);

	/// <summary>
	/// Setup camera
	/// </summary>
	CCamera* camera = new CCamera(CAMERA_WIDTH * CAMERA_SCALE, CAMERA_HEIGHT* CAMERA_SCALE, CAMERA_SCALE);
	CCamera::SetInstance(*camera);
	
	//mapGrid = DivideGrids(GAME_WIDTH, GAME_HEIGHT, GRID_WIDTH, GRID_HEIGHT);
	//grid_count_width = mapGrid[0].size();
	//grid_count_height = mapGrid.size();

	manager.Init();
}

void CGame::LoadResources()
{
	LoadTextures();
	LoadSprites();

	manager.LoadResources();
}

void CGame::LoadTextures()
{
	//CTextureLibrary::GetInstance()->Add(CAR_TEXTURE, L"Resources/Texture/My car spritesheet.png");
	CTextureLibrary::GetInstance()->Add(PLAYER_TEXTURE, PLAYER_TEXTURE_PATH);
	CTextureLibrary::GetInstance()->Add(ENEMIES_TEXTURE, ENEMIES_TEXTURE_PATH);
	CTextureLibrary::GetInstance()->Add(PLAYER_HEALTH_TEXTURE, PLAYER_HEALTH_TEXTURE_PATH);
	CTextureLibrary::GetInstance()
		->Add(ID_TEX_BBOX, TEX_BBOX_PATH);
	CTextureLibrary::GetInstance()->Add(OTHER_OBJECTS_TEXTURE, OTHER_OBJECTS_TEXTURE_PATH);
	CTextureLibrary::GetInstance()->Add(BLACK_SCREEN_TEXTURE, BLACK_SCREEN_TEXTURE_PATH);
	CTextureLibrary::GetInstance()->Add(BOSS_TEXTURE, BOSS_TEXTURE_PATH);
	CTextureLibrary::GetInstance()->Add(OPENING_TEXTURE, OPENING_TEXTURE_PATH);
	CTextureLibrary::GetInstance()->Add(ROLLOUT_TEXTURE, ROLLOUT_TEXTURE_PATH);
	CTextureLibrary::GetInstance()->Add(ITEMS_TEXTURE, ITEMS_TEXTURE_PATH);
}

void CGame::LoadSprites()
{
	LPDIRECT3DTEXTURE9 textPlayer = CTextureLibrary::GetInstance()->Get(PLAYER_TEXTURE);
	LPDIRECT3DTEXTURE9 textEnemies = CTextureLibrary::GetInstance()->Get(ENEMIES_TEXTURE);
	LPDIRECT3DTEXTURE9 textPlayerHealth = CTextureLibrary::GetInstance()->Get(PLAYER_HEALTH_TEXTURE);
	LPDIRECT3DTEXTURE9 textOtherObjects = CTextureLibrary::GetInstance()->Get(OTHER_OBJECTS_TEXTURE);
	LPDIRECT3DTEXTURE9 textBoss = CTextureLibrary::GetInstance()->Get(BOSS_TEXTURE);
	LPDIRECT3DTEXTURE9 textOpening = CTextureLibrary::GetInstance()->Get(OPENING_TEXTURE);
	LPDIRECT3DTEXTURE9 textRollOut = CTextureLibrary::GetInstance()->Get(ROLLOUT_TEXTURE);
	LPDIRECT3DTEXTURE9 textItems = CTextureLibrary::GetInstance()->Get(ITEMS_TEXTURE);
	CSpriteLibrary* lib = CSpriteLibrary::GetInstance();

	lib->Add(
		ID_BLACK_SCREEN,
		0, 0,
		CAMERA_WIDTH * CAMERA_SCALE,
		CAMERA_HEIGHT * CAMERA_SCALE,
		CTextureLibrary::GetInstance()->Get(BLACK_SCREEN_TEXTURE)
	);

	#pragma region SOPHIA SPRITES
	lib->Add(ID_SOPHIA_GUN_LEFT, 11, 4, 18, 8, textPlayer);
	lib->Add(ID_SOPHIA_GUN_RIGHT, 12, 13, 19, 17, textPlayer);
	lib->Add(ID_SOPHIA_GUN_UPLEFT, 20, 2, 28, 10, textPlayer);
	lib->Add(ID_SOPHIA_GUN_UPRIGHT, 20, 11, 28, 19, textPlayer);
	lib->Add(ID_SOPHIA_GUN_UP, 31, 2, 35, 9, textPlayer);

	lib->Add(ID_SOPHIA_HEAD_LEFT, 2, 20, 18, 28, textPlayer);
	lib->Add(ID_SOPHIA_HEAD_RIGHT, 2, 29, 18, 37, textPlayer);
	lib->Add(ID_SOPHIA_HEAD_UPLEFT, 56, 21, 56 + 16, 36, textPlayer);
	lib->Add(ID_SOPHIA_HEAD_UPRIGHT, 38, 21, 38 + 16, 35, textPlayer);

	lib->Add(ID_SOPHIA_HEAD_EJECT_JASON_LEFT_1, 109, 12, 109 + 16, 12 + 15, textPlayer);
	lib->Add(ID_SOPHIA_HEAD_EJECT_JASON_LEFT_2, 126, 12, 126 + 16, 12 + 15, textPlayer);
	lib->Add(ID_SOPHIA_HEAD_EJECT_JASON_RIGHT_1, 109, 30, 109 + 16, 30 + 15, textPlayer);
	lib->Add(ID_SOPHIA_HEAD_EJECT_JASON_RIGHT_2, 126, 30, 126 + 16, 30 + 15, textPlayer);

	lib->Add(ID_SOPHIA_BODY, 109, 2, 115, 9, textPlayer);
	lib->Add(ID_SOPHIA_BODY_UPRIGHT, 135, 2, 143, 10, textPlayer);
	lib->Add(ID_SOPHIA_BODY_UPLEFT, 126, 2, 134, 10, textPlayer);

	lib->Add(ID_SOPHIA_WHEEL_1, 38, 11, 45, 19, textPlayer);
	lib->Add(ID_SOPHIA_WHEEL_2, 47, 11, 54, 19, textPlayer);
	lib->Add(ID_SOPHIA_WHEEL_3, 56, 11, 63, 19, textPlayer);
	lib->Add(ID_SOPHIA_WHEEL_4, 65, 11, 72, 19, textPlayer);
	lib->Add(ID_SOPHIA_WHEEL_5, 38, 2, 45, 10, textPlayer);
	lib->Add(ID_SOPHIA_WHEEL_6, 47, 2, 54, 10, textPlayer);
	lib->Add(ID_SOPHIA_WHEEL_7, 56, 2, 63, 10, textPlayer);
	lib->Add(ID_SOPHIA_WHEEL_8, 65, 2, 72, 10, textPlayer);

	lib->Add(ID_SOPHIA_GUN_LEFT_WHITE, 83, 36, 83 + 7, 36 + 4, textPlayer);
	lib->Add(ID_SOPHIA_GUN_RIGHT_WHITE, 84, 45, 84 + 7, 45 + 4, textPlayer);
	lib->Add(ID_SOPHIA_GUN_UPLEFT_WHITE, 92, 34, 92 + 8, 34 + 8, textPlayer);
	lib->Add(ID_SOPHIA_GUN_UPRIGHT_WHITE, 92, 43, 92 + 8, 43 + 8, textPlayer);
	lib->Add(ID_SOPHIA_GUN_UP_WHITE, 103, 34, 103 + 4, 34 + 7, textPlayer);

	lib->Add(ID_SOPHIA_HEAD_LEFT_WHITE, 74, 53, 74 + 16, 53 + 8, textPlayer);
	lib->Add(ID_SOPHIA_HEAD_RIGHT_WHITE, 74, 62, 74 + 16, 62 + 8, textPlayer);
	lib->Add(ID_SOPHIA_HEAD_UPLEFT_WHITE, 128, 54, 128 + 16, 54 + 15, textPlayer);
	lib->Add(ID_SOPHIA_HEAD_UPRIGHT_WHITE, 110, 54, 110 + 16, 54 + 15, textPlayer);

	lib->Add(ID_SOPHIA_BULLET_LEFT, 74, 3, 74 + 24, 3 + 6, textPlayer);
	lib->Add(ID_SOPHIA_BULLET_RIGHT, 74, 12, 74 + 24, 12 + 6, textPlayer);
	lib->Add(ID_SOPHIA_BULLET_UP, 100, 2, 100 + 6, 2 + 24, textPlayer);

	lib->Add(ID_SOPHIA_MISSILE_HEAD_LEFT, 154, 88, 154 + 7, 88 + 7, textPlayer);
	lib->Add(ID_SOPHIA_MISSILE_HEAD_UP, 161, 81, 161 + 7, 81 + 7, textPlayer);
	lib->Add(ID_SOPHIA_MISSILE_HEAD_RIGHT, 168, 88, 168 + 7, 88 + 7, textPlayer);
	lib->Add(ID_SOPHIA_MISSILE_HEAD_DOWN, 161, 95, 161 + 7, 95 + 7, textPlayer);

	//lib->Add(ID_SOPHIA_MISSILE_TAIL_LEFT, 178, 86, 178 + 7, 86 + 12, textPlayer);
	//lib->Add(ID_SOPHIA_MISSILE_TAIL_UP, 186, 78, 186 + 12, 78 + 7, textPlayer);
	//lib->Add(ID_SOPHIA_MISSILE_TAIL_RIGHT, 199, 86, 199 + 7, 86 + 12, textPlayer);
	//lib->Add(ID_SOPHIA_MISSILE_TAIL_DOWN, 186, 99, 186 + 12, 99 + 7, textPlayer);
	lib->Add(ID_SOPHIA_MISSILE_TAIL_LEFT, 74, 149, 74 + 8, 149 + 8, textPlayer);
	lib->Add(ID_SOPHIA_MISSILE_TAIL_UP, 83, 149, 83 + 8, 149 + 8, textPlayer);
	lib->Add(ID_SOPHIA_MISSILE_TAIL_RIGHT, 92, 149, 92 + 8, 149 + 8, textPlayer);
	lib->Add(ID_SOPHIA_MISSILE_TAIL_DOWN, 101, 149, 101 + 8, 149 + 8, textPlayer);
	#pragma endregion


	lib->Add(ID_TEXT_HOV, 0, 0, 11, 35, textPlayerHealth);
	lib->Add(ID_TEXT_POW, 0, 58, 11, 93, textPlayerHealth);
	lib->Add(ID_SOPHIA_HEALTH_BAR, 0, 43, 11, 48, textPlayerHealth);
	lib->Add(ID_JASON_HEALTH_BAR, 0, 50, 11, 55, textPlayerHealth);

	#pragma region JASON SPRITES
	lib->Add(ID_JASON_WALK_LEFT_1, 2, 38,	2 + 8, 38 + 16, textPlayer);
	lib->Add(ID_JASON_WALK_LEFT_2, 11, 38, 11 + 8, 38 + 16, textPlayer);
	lib->Add(ID_JASON_WALK_LEFT_3, 20, 38, 20 + 8, 38 + 16, textPlayer);
	lib->Add(ID_JASON_WALK_LEFT_4, 29, 38, 29 + 8, 38 + 16, textPlayer);

	lib->Add(ID_JASON_WALK_RIGHT_1, 2, 55,	2 + 8, 55 + 16, textPlayer);
	lib->Add(ID_JASON_WALK_RIGHT_2, 11, 55, 11 + 8, 55 + 16, textPlayer);
	lib->Add(ID_JASON_WALK_RIGHT_3, 20, 55, 20 + 8, 55 + 16, textPlayer);
	lib->Add(ID_JASON_WALK_RIGHT_4, 29, 55, 29 + 8, 55 + 16, textPlayer);

	lib->Add(ID_JASON_CRAWL_LEFT_1, 2, 139, 2 + 15, 139 + 8, textPlayer);
	lib->Add(ID_JASON_CRAWL_LEFT_2, 20, 139, 20 + 15, 139 + 8, textPlayer);
	lib->Add(ID_JASON_CRAWL_RIGHT_1, 38, 139, 38 + 15, 139 + 8, textPlayer);
	lib->Add(ID_JASON_CRAWL_RIGHT_2, 56, 139, 56 + 15, 139 + 8, textPlayer);

	lib->Add(ID_JASON_BULLET, 94, 141, 94 + 5, 141 + 4, textPlayer);
	#pragma endregion

	#pragma region JASON TOP DOWN SPRITES
	lib->Add(ID_JASON_TOPDOWN_WALK_LEFT_1, 77, 72, 77 + 24, 72 + 32, textPlayer);
	lib->Add(ID_JASON_TOPDOWN_WALK_LEFT_2, 102, 72, 102 + 24, 72 + 32, textPlayer);
	lib->Add(ID_JASON_TOPDOWN_WALK_LEFT_3, 127, 72, 127 + 24, 72 + 32, textPlayer);

	lib->Add(ID_JASON_TOPDOWN_WALK_UP_1, 4, 105, 4 + 20, 105 + 32, textPlayer);
	lib->Add(ID_JASON_TOPDOWN_WALK_UP_2, 29, 105, 29 + 20, 105 + 32, textPlayer);
	lib->Add(ID_JASON_TOPDOWN_WALK_UP_3, 54, 105, 54 + 20, 105 + 32, textPlayer);

	lib->Add(ID_JASON_TOPDOWN_WALK_RIGHT_1, 77, 105, 77 + 24, 105 + 32, textPlayer);
	lib->Add(ID_JASON_TOPDOWN_WALK_RIGHT_2, 102, 105, 102 + 24, 105 + 32, textPlayer);
	lib->Add(ID_JASON_TOPDOWN_WALK_RIGHT_3, 127, 105, 127 + 24, 105 + 32, textPlayer);

	lib->Add(ID_JASON_TOPDOWN_WALK_DOWN_1, 4, 72, 4 + 20, 72 + 32, textPlayer);
	lib->Add(ID_JASON_TOPDOWN_WALK_DOWN_2, 29, 72, 29 + 20, 72 + 32, textPlayer);
	lib->Add(ID_JASON_TOPDOWN_WALK_DOWN_3, 54, 72, 54 + 20, 72 + 32, textPlayer);

	lib->Add(ID_JASON_TOPDOWN_BULLET_LEFT, 74, 150, 74 + 8, 150 + 6, textPlayer);
	lib->Add(ID_JASON_TOPDOWN_BULLET_UP, 84, 149, 84 + 6, 149 + 8, textPlayer);
	lib->Add(ID_JASON_TOPDOWN_BULLET_RIGHT, 92, 150, 92 + 8, 150 + 6, textPlayer);
	lib->Add(ID_JASON_TOPDOWN_BULLET_DOWN, 102, 149, 102 + 6, 149 + 8, textPlayer);
	#pragma endregion

#pragma region ITEMS
	lib->Add(ID_PLAYER_UPGRADE, 100, 8, 100 + 25, 8 + 17, textItems);
	lib->Add(ID_HEALTH_BALL, 105, 109, 105 + 16, 109 + 16, textItems);
	lib->Add(ID_ENERGY_BALL, 155, 109, 155 + 16, 109 + 16, textItems);
	lib->Add(ID_POWER_BALL, 255, 109, 255 + 16, 109 + 16, textItems);
#pragma endregion

#pragma region EXPLOSION
	lib->Add(ID_EXPLOSION_1, 145, 8, 145 + 8, 8 + 8, textPlayer);
	lib->Add(ID_EXPLOSION_2, 154, 6, 154 + 16, 6 + 16, textPlayer);
	lib->Add(ID_EXPLOSION_3, 171, 6, 171 + 16, 6 + 16, textPlayer);
	lib->Add(ID_EXPLOSION_4, 188, 2, 188 + 24, 2 + 24, textPlayer);
#pragma endregion


	// ENEMIES
#pragma region WORM
	lib->Add(ID_WORM_MOVE_LEFT_1, 46, 412, 64, 422, textEnemies);
	lib->Add(ID_WORM_MOVE_LEFT_2, 64, 412, 82, 422, textEnemies);
	lib->Add(ID_WORM_MOVE_RIGHT_1, 172, 412, 190, 422, textEnemies);
	lib->Add(ID_WORM_MOVE_RIGHT_2, 192, 412, 210, 422, textEnemies);
#pragma endregion

#pragma region DOME
	lib->Add(ID_DOME_UP_MOVE_RIGHT_1, 67, 424, 85, 443, textEnemies);
	lib->Add(ID_DOME_UP_MOVE_RIGHT_2, 87, 424, 105, 443, textEnemies);
	lib->Add(ID_DOME_UP_MOVE_LEFT_1, 149, 424, 167, 443, textEnemies);
	lib->Add(ID_DOME_UP_MOVE_LEFT_2, 169, 424, 187, 443, textEnemies);

	lib->Add(ID_DOME_DOWN_MOVE_RIGHT_1, 67, 479, 85, 498, textEnemies);
	lib->Add(ID_DOME_DOWN_MOVE_RIGHT_2, 87, 479, 105, 498, textEnemies);
	lib->Add(ID_DOME_DOWN_MOVE_LEFT_1, 149, 479, 167, 498, textEnemies);
	lib->Add(ID_DOME_DOWN_MOVE_LEFT_2, 169, 479, 187, 498, textEnemies);

	lib->Add(ID_DOME_LEFT_MOVE_UP_1, 50, 461, 68, 479, textEnemies);
	lib->Add(ID_DOME_LEFT_MOVE_UP_2, 51, 441, 69, 459, textEnemies);
	lib->Add(ID_DOME_LEFT_MOVE_DOWN_1, 133, 441, 151, 459, textEnemies);
	lib->Add(ID_DOME_LEFT_MOVE_DOWN_2, 132, 461, 150, 479, textEnemies);

	lib->Add(ID_DOME_RIGHT_MOVE_UP_1, 187, 461, 205, 479, textEnemies);
	lib->Add(ID_DOME_RIGHT_MOVE_UP_2, 187, 441, 205, 459, textEnemies);
	lib->Add(ID_DOME_RIGHT_MOVE_DOWN_1, 105, 441, 123, 459, textEnemies);
	lib->Add(ID_DOME_RIGHT_MOVE_DOWN_2, 105, 461, 123, 479, textEnemies);
#pragma endregion

#pragma region JUMPER
	lib->Add(ID_JUMPER_MOVE_LEFT_1, 67, 499, 84, 525, textEnemies);
	lib->Add(ID_JUMPER_MOVE_LEFT_2, 85, 499, 102, 525, textEnemies);
	lib->Add(ID_JUMPER_MOVE_LEFT_3, 105, 499, 122, 525, textEnemies);
	lib->Add(ID_JUMPER_MOVE_RIGHT_1, 132, 499, 149, 525, textEnemies);
	lib->Add(ID_JUMPER_MOVE_RIGHT_2, 152, 499, 169, 525, textEnemies);
	lib->Add(ID_JUMPER_MOVE_RIGHT_3, 170, 499, 187, 525, textEnemies);
#pragma endregion

#pragma region ORB
	lib->Add(ID_ORB_1, 78, 387, 96, 405, textEnemies);
	lib->Add(ID_ORB_2, 98, 387, 116, 405, textEnemies);
	lib->Add(ID_ORB_3, 118, 387, 136, 405, textEnemies);
	lib->Add(ID_ORB_4, 138, 387, 156, 405, textEnemies);
	lib->Add(ID_ORB_5, 158, 387, 176, 405, textEnemies);
#pragma endregion

#pragma region SKULL
	lib->Add(ID_SKULL_MOVE_LEFT_1, 42, 530, 42 + 18, 530 + 18, textEnemies);
	lib->Add(ID_SKULL_MOVE_LEFT_2, 62, 527, 62 + 18, 527 + 21, textEnemies);

	lib->Add(ID_SKULL_MOVE_RIGHT_1, 194, 530, 194 + 18, 530 + 18, textEnemies);
	lib->Add(ID_SKULL_MOVE_RIGHT_2, 174, 527, 174 + 18, 527 + 21, textEnemies);
#pragma endregion

#pragma region FLOATER
	lib->Add(ID_FLOATER_MOVE_1, 84, 407, 84 + 18, 407 + 15, textEnemies);
	lib->Add(ID_FLOATER_MOVE_2, 104, 406, 104 + 18, 406 + 16, textEnemies);
#pragma endregion

#pragma region INSECT
	lib->Add(ID_INSECT_MOVE_LEFT_1, 84, 533, 84 + 18, 533 + 15, textEnemies);
	lib->Add(ID_INSECT_MOVE_LEFT_2, 104, 530, 104 + 18, 530 + 18, textEnemies);

	lib->Add(ID_INSECT_MOVE_RIGHT_1, 152, 533, 152 + 18, 533 + 15, textEnemies);
	lib->Add(ID_INSECT_MOVE_RIGHT_2, 132, 530, 132 + 18, 530 + 18, textEnemies);
#pragma endregion


#pragma region WALKER
	lib->Add(ID_WALKER_1, 84, 296, 102, 313, textEnemies);
	lib->Add(ID_WALKER_2, 104, 296, 122, 313, textEnemies);
	lib->Add(ID_WALKER_3, 132, 296, 150, 313, textEnemies);
	lib->Add(ID_WALKER_4, 152, 296, 170, 313, textEnemies);
#pragma endregion

#pragma region DASHER
	lib->Add(ID_DASHER_IDLE_1, 44, 277, 44 + 18, 277 + 16, textEnemies);
	lib->Add(ID_DASHER_IDLE_2, 84, 277, 84 + 18, 277 + 16, textEnemies);
	lib->Add(ID_DASHER_IDLE_3, 152, 277, 152 + 18, 277 + 16, textEnemies);
	lib->Add(ID_DASHER_IDLE_4, 192, 277, 192 + 18, 277 + 16, textEnemies);

	lib->Add(ID_DASHER_MOVE_1, 44, 277, 44 + 18, 277 + 16, textEnemies);
	lib->Add(ID_DASHER_MOVE_2, 64, 275, 64 + 18, 275 + 16, textEnemies);
	lib->Add(ID_DASHER_MOVE_3, 152, 277, 152 + 18, 277 + 16, textEnemies);
	lib->Add(ID_DASHER_MOVE_4, 132, 275, 132 + 18, 275 + 16, textEnemies);
#pragma endregion

#pragma region HEAD
	lib->Add(ID_HEAD_LEFT_1, 67, 351, 67 + 26, 351 + 34, textEnemies);
	lib->Add(ID_HEAD_LEFT_2, 96, 352, 96 + 26, 352 + 33, textEnemies);
	lib->Add(ID_HEAD_RIGHT_1, 161, 351, 161 + 26, 351 + 34, textEnemies);
	lib->Add(ID_HEAD_RIGHT_2, 132, 352, 132 + 26, 352 + 33, textEnemies);
#pragma endregion

#pragma region SPIRAL
	lib->Add(ID_SPIRAL_LEFT_1, 65, 316, 65 + 26, 316 + 33, textEnemies);
	lib->Add(ID_SPIRAL_LEFT_2, 96, 316, 96 + 26, 316 + 33, textEnemies);
	lib->Add(ID_SPIRAL_RIGHT_1, 163, 316, 163 + 26, 316 + 33, textEnemies);
	lib->Add(ID_SPIRAL_RIGHT_2, 132, 316, 132 + 26, 316 + 33, textEnemies);
#pragma endregion

#pragma region TELEPORTER
	lib->Add(ID_TELEPORTER_LEFT_1, 71, 568, 71 + 24, 568 + 32, textEnemies);
	lib->Add(ID_TELEPORTER_LEFT_2, 98, 568, 98 + 24, 568 + 32, textEnemies);
	lib->Add(ID_TELEPORTER_RIGHT_1, 159, 568, 159 + 24, 568 + 32, textEnemies);
	lib->Add(ID_TELEPORTER_RIGHT_2, 132, 568, 132 + 24, 568 + 32, textEnemies);
#pragma endregion

#pragma region EYEBALL
	lib->Add(ID_EYEBALL_1, 102, 550, 102 + 16, 550 + 16, textEnemies);
	lib->Add(ID_EYEBALL_2, 119, 550, 119 + 16, 550 + 16, textEnemies);
	lib->Add(ID_EYEBALL_3, 136, 550, 136 + 16, 550 + 16, textEnemies);
#pragma endregion

#pragma region CANON
	lib->Add(ID_CANON_1, 96, 603, 96 + 26, 603 + 26, textEnemies);
	lib->Add(ID_CANON_2, 70, 603, 70 + 22, 603 + 26, textEnemies);
	lib->Add(ID_CANON_3, 41, 607, 41 + 26, 607 + 22, textEnemies);
#pragma endregion

#pragma region ENEMY BULLET
	lib->Add(ID_MINE_BULLET, 32, 305, 40, 313, textEnemies);
	lib->Add(ID_SKULL_BULLET, 51, 515, 61, 525, textEnemies);

	lib->Add(ID_ENEMY_SIDESCROLL_BULLET_1, 51, 515, 61, 525, textEnemies);
	lib->Add(ID_ENEMY_SIDESCROLL_BULLET_2, 32, 305, 32 + 8, 305 + 8, textEnemies);

	lib->Add(ID_ENEMY_TOPDOWN_BULLET_1, 51, 1370, 51 + 10, 1370 + 10, textEnemies);
	lib->Add(ID_ENEMY_TOPDOWN_BULLET_2, 51, 1370, 51 + 10, 1370 + 10, textEnemies);
#pragma endregion

#pragma region BOSS
	lib->Add(ID_BOSS_HEAD_1, 80, 303, 80 + 60, 303 + 64, textBoss);
	lib->Add(ID_BOSS_HEAD_2, 146, 302, 146 + 60, 302 + 65, textBoss);
	lib->Add(ID_BOSS_HEAD_3, 213, 303, 213 + 60, 303 + 64, textBoss);
	lib->Add(ID_BOSS_HEAD_4, 280, 302, 280 + 60, 302 + 65, textBoss);

	lib->Add(ID_BOSS_HEAD_5, 83, 371, 83 + 60, 371 + 65, textBoss);
	lib->Add(ID_BOSS_HEAD_6, 147, 370, 147 + 60, 370 + 66, textBoss);
	lib->Add(ID_BOSS_HEAD_7, 212, 371, 212 + 60, 371 + 65, textBoss);
	lib->Add(ID_BOSS_HEAD_8, 277, 370, 277 + 60, 370 + 66, textBoss);

	lib->Add(ID_BOSS_LEFT_ARM, 222, 1129, 222 + 16, 1129 + 17, textBoss);
	lib->Add(ID_BOSS_LEFT_HAND, 218, 1147, 218 + 18, 1147 + 32, textBoss);

	lib->Add(ID_BOSS_RIGHT_ARM, 188, 1129, 188 + 16, 1129 + 17, textBoss);
	lib->Add(ID_BOSS_RIGHT_HAND, 190, 1147, 190 + 18, 1147 + 32, textBoss);
#pragma endregion

#pragma region OPENING
	lib->Add(ID_OPENING_1, 0, 0, 0 + 256, 0 + 224, textOpening);
	lib->Add(ID_OPENING_2, 259, 0, 259 + 256, 0 + 224, textOpening);
	lib->Add(ID_OPENING_3, 518, 0, 518 + 256, 0 + 224, textOpening);
	lib->Add(ID_OPENING_4, 777, 0, 777 + 256, 0 + 224, textOpening);

	lib->Add(ID_OPENING_5, 0, 227, 0 + 256, 227 + 224, textOpening);
	lib->Add(ID_OPENING_6, 259, 227, 259 + 256, 227 + 224, textOpening);
	lib->Add(ID_OPENING_7, 518, 227, 518 + 256, 277 + 224, textOpening);
	lib->Add(ID_OPENING_8, 777, 227, 777 + 256, 227 + 224, textOpening);

	lib->Add(ID_OPENING_9, 0, 454, 0 + 256, 454 + 224, textOpening);
	lib->Add(ID_OPENING_10, 259, 454, 259 + 256, 454 + 224, textOpening);
	lib->Add(ID_OPENING_11, 518, 454, 518 + 256, 454 + 224, textOpening);
	lib->Add(ID_OPENING_12, 777, 454, 777 + 256, 454 + 224, textOpening);

	lib->Add(ID_OPENING_13, 0, 681, 0 + 256, 681 + 224, textOpening);
	lib->Add(ID_OPENING_14, 259, 681, 259 + 256, 681 + 224, textOpening);
	lib->Add(ID_OPENING_15, 518, 681, 518 + 256, 681 + 224, textOpening);
	lib->Add(ID_OPENING_16, 777, 681, 777 + 256, 681 + 224, textOpening);

	lib->Add(ID_OPENING_17, 0, 908, 0 + 256, 908 + 224, textOpening);
	lib->Add(ID_OPENING_18, 259, 908, 259 + 256, 908 + 224, textOpening);
	lib->Add(ID_OPENING_19, 518, 908, 518 + 256, 908 + 224, textOpening);
	lib->Add(ID_OPENING_20, 777, 908, 777 + 256, 908 + 224, textOpening);

	lib->Add(ID_OPENING_21, 0, 1135, 0 + 256, 1135 + 224, textOpening);
	lib->Add(ID_OPENING_22, 259, 1135, 259 + 256, 1135 + 224, textOpening);
	lib->Add(ID_OPENING_23, 518, 1135, 518 + 256, 1135 + 224, textOpening);
	lib->Add(ID_OPENING_24, 777, 1135, 777 + 256, 1135 + 224, textOpening);

	lib->Add(ID_OPENING_25, 0, 1362, 0 + 256, 1362 + 224, textOpening);
	lib->Add(ID_OPENING_26, 259, 1362, 259 + 256, 1362 + 224, textOpening);
	lib->Add(ID_OPENING_27, 518, 1362, 518 + 256, 1362 + 224, textOpening);
	lib->Add(ID_OPENING_28, 777, 1362, 777 + 256, 1362 + 224, textOpening);

	lib->Add(ID_OPENING_29, 0, 1589, 0 + 256, 1589 + 224, textOpening);
	lib->Add(ID_OPENING_30, 259, 1589, 259 + 256, 1589 + 224, textOpening);
	lib->Add(ID_OPENING_31, 518, 1589, 518 + 256, 1589 + 224, textOpening);
	lib->Add(ID_OPENING_32, 777, 1589, 777 + 256, 1589 + 224, textOpening);

	lib->Add(ID_OPENING_33, 0, 1816, 0 + 256, 1816 + 224, textOpening);
	lib->Add(ID_OPENING_34, 259, 1816, 259 + 256, 1816 + 224, textOpening);
	lib->Add(ID_OPENING_35, 518, 1816, 518 + 256, 1816 + 224, textOpening);
	lib->Add(ID_OPENING_36, 777, 1816, 777 + 256, 1816 + 224, textOpening);

	lib->Add(ID_OPENING_37, 0, 2043, 0 + 256, 2043 + 224, textOpening);
#pragma endregion

#pragma region ROLLOUT
	lib->Add(ID_ROLLOUT_1, 0, 0, 0 + 256, 0 + 224, textRollOut);
	lib->Add(ID_ROLLOUT_2, 259, 0, 259 + 256, 0 + 224, textRollOut);
	lib->Add(ID_ROLLOUT_3, 518, 0, 518 + 256, 0 + 224, textRollOut);

	lib->Add(ID_ROLLOUT_4, 0, 227, 0 + 256, 227 + 224, textRollOut);
	lib->Add(ID_ROLLOUT_5, 259, 227, 259 + 256, 227 + 224, textRollOut);
	lib->Add(ID_ROLLOUT_6, 518, 227, 518 + 256, 227 + 224, textRollOut);

	lib->Add(ID_ROLLOUT_7, 0, 454, 0 + 256, 454 + 224, textRollOut);
	lib->Add(ID_ROLLOUT_8, 259, 454, 259 + 256, 454 + 224, textRollOut);
	lib->Add(ID_ROLLOUT_9, 518, 454, 518 + 256, 454 + 224, textRollOut);

	lib->Add(ID_ROLLOUT_10, 0, 681, 0 + 256, 681 + 224, textRollOut);
#pragma endregion

	//84	296	18	17
	//	104	297	18	16

	//	132	297	18	16
	//	152	296	18	17

	//other object sprite
	lib->Add(ID_BREAKABLE_WALL, 1, 35, 17, 51, textOtherObjects);
}

void CGame::Run()
{
	//Load resource to the game
	LoadResources();

	MSG msg;
	int64_t done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	try
	{
		while (!done)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) done = 1;

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			DWORD now = GetTickCount();

			// dt: the time between (beginning of last frame) and now
			// this frame: the frame we are about to render
			DWORD dt = now - frameStart;

			//Heart of the game
			if (dt >= tickPerFrame)
			{
				frameStart = now;

				Update(dt/10);
				Render();
			}
			//else
			//	Sleep(tickPerFrame - dt);
		}
	}
	catch (const std::exception& ex)
	{
		DebugOut(L"[ERROR] Exception in Run method in Game %s\n", ex.what());
		return;
	}

	//Clean the resources
	CleanResources();
}

void CGame::Update(DWORD dt)
{
	manager.Update(dt);
}

void CGame::Render()
{
	LPDIRECT3DDEVICE9 d3ddev = CGraphic::Instance->GetDirect3DDevice();
	LPD3DXSPRITE spriteHandler = CGraphic::Instance->GetSpriteHandler();
	LPDIRECT3DSURFACE9 backBuffer = CGraphic::Instance->GetBackBuffer();

	if (d3ddev->BeginScene() == D3D_OK)
	{
		// Clear the whole window with a color
		d3ddev->ColorFill(backBuffer, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		//Render these
		//tiles -> enemies -> player -> portals
		//RenderTiles();
		//RenderEnemies();

		//CSophiaFake::GetInstance()->Render();
		//RenderPlayer();

		//RenderPortals();

		manager.Render();

		spriteHandler->End();
		d3ddev->EndScene();
	}

	// Display back buffer content to the screen
	d3ddev->Present(NULL, NULL, NULL, NULL);

	//ExecuteRequests(CGameRequest::RequestList);
}

void CGame::CleanResources()
{
	CGraphic::Instance->End();
	Sound::DirectSound_Shutdown();
}


CGame::~CGame()
{
}

HWND CreateGameWindow(HINSTANCE hInstance, int64_t nCmdShow, int64_t ScreenWidth, int64_t ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	//Try this to see how the debug function prints out file and line 
	//wc.hInstance = (HINSTANCE)-100; 

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		DWORD ErrCode = GetLastError();
		MessageBox(hWnd, L"Error create window handle", L"Error", MB_OK);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}


LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_KILLFOCUS:
		break;
	case WM_SETFOCUS:
		break;
		//if the player close the window
	case WM_DESTROY:
		//tell window to kill this program
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

