#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_
#include<Windows.h>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<iostream>
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static SDL_Surface* g_screen_surface = NULL;
static Mix_Music* g_music=NULL;
static Mix_Chunk* g_worm = NULL;
static Mix_Chunk* g_eatapple = NULL;
static Mix_Chunk* g_next = NULL;
static Mix_Chunk* g_wineffect = NULL;
extern bool g_effectOn;
//screen
const int SCREEN_WIDTH = 1248;
const int SCREEN_HEIGHT = 624;
const int SCREEN_BPP = 32;
//color key
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int RENDER_DRAW_COLOR = 155;
#define TILE_SIZE 26
#define MAX_MAP_X 48
#define MAX_MAP_Y 24


enum Direction
{
	UP=0, DOWN, LEFT, RIGHT, NONE
};
struct Position
{
    int x;
    int y;


    Position(int x_, int y_) : x(x_), y(y_) {}


    bool operator==(Position p) {
        return x == p.x && y == p.y;
    }
	bool operator!=(Position p) {
		return x != p.x || y != p.y;
	}
};



 struct Map
{
	int start_x;
	int start_y;
	int max_x;
	int max_y;
	int tile[MAX_MAP_Y][MAX_MAP_X];
	std::string file_name_;
    
};



#endif 