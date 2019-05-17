#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


#include <string>
#include <Windows.h>
#include <iostream>
#include <vector>



static SDL_Window*    g_window = NULL;
static SDL_Renderer*  g_screen = NULL;
static SDL_Event     g_event;
static SDL_Surface*    g_img_menu = NULL;

	


//SCREEN
const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH  = 1280;
const int SCREEN_BPP    = 32; 

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff; 



#define TILE_SIZE 32

#define MAX_MAP_X 1000
#define MAX_MAP_Y 20

struct Map
{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name_;
};
const int SPEED_MAP = 5;


#endif 
