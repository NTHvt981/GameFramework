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

#define WINDOW_CLASS_NAME L"NGUYEN TRUNG HIEU'S WINDOW"
#define WINDOW_TITLE L"Test 1"
#define WINDOW_ICON_PATH L".\Resources\Texture\brick.ico" 
#define D3DCOLOR_WHITE D3DCOLOR_XRGB(255, 255, 255)

#define FULLSCREEN false

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define MAX_FRAME_RATE 120


#define BRICK_TEXTURE_PATH L"..\..\Resources\Texture\brick.png"
#define BRICK_START_X 30.0f
#define BRICK_START_Y 10.0f
#define BRICK_START_VX 0.2f
#define BRICK_WIDTH 16.0f
