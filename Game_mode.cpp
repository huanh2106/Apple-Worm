#include "Game_mode.h"
#include <iostream>
using namespace std;
#define playX 544
#define playY 375
#define playW 160
#define playH 110
BaseObject g_background;
void GameMode::initData() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	g_window = SDL_CreateWindow("Apple Worm by Huy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == nullptr) {
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	if (g_screen == nullptr) {
		std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	g_screen_surface = SDL_GetWindowSurface(g_window);
	SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
}

bool LoadBackground() {
	if (!g_background.LoadImg("image//background.png", g_screen)) {
		std::cout << "Failed to load background image!" << std::endl;
		return false;
	}
	
	return true;
}



void close() {
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	SDL_DestroyWindow(g_window);
	IMG_Quit();
	SDL_Quit();
}

GameMode::GameMode()
{
	state = Menu;
	initData();
}
GameMode::~GameMode()
{
}
void GameMode::run(SDL_Event& e)
{
	
	bool quit = false;
	while (!quit)
	{

		if (state == Menu)
		{
			drawMenu(g_screen);
			handleMenu(e, quit);

		}
		else if (state == ChooseLV)
		{
			drawChooseLV(g_screen);
			handleChooseLV(e, quit);
		}
		else if (state == Lv1)
		{
			handleLv1(e, quit);
		}
		else if (state == Lv2)
		{
			
		}
	}
	close();
}
	
	
    
bool GameMode::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == true)
	{

	}
	return ret;
}
void GameMode::drawMenu(SDL_Renderer* screen)
{  
	if (!LoadImg("menu//menubackground.png", screen))
	{
		cout<<"load menu fail";
	}
	SDL_Rect rectbackgroundmenu;
	rectbackgroundmenu.x = 0;
	rectbackgroundmenu.y = 0;
	rectbackgroundmenu.w = SCREEN_WIDTH;
	rectbackgroundmenu.h = SCREEN_HEIGHT;
	SDL_RenderCopy(screen, p_object, NULL, &rectbackgroundmenu);
	SDL_Rect playRect = {playX , playY, playW, playH };
	if (!LoadImg("menu//play.png", screen))
	{
		cout << "load menu fail";
	}
	SDL_RenderCopy(screen, p_object, NULL, &playRect);
    SDL_RenderPresent(screen);
}
void GameMode::handleMenu(SDL_Event& e, bool& quit ) {
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			quit = true;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			if (mouseX >= playX && mouseX <= playX + playW && mouseY >= playY && mouseY <= playY + playH) {
				state = ChooseLV;
			}

		}


	}

}



void GameMode::handleLv1(SDL_Event& e, bool& quit)
{
	
	LoadBackground();

	GameMap game_map;
    game_map.LoadMap("map//map01.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(8, 7);
    Worm worm(&game_map);
	worm.SetWorm(newPosWorm);
	Apple apple;
	Destination destination;
	Position newPos(15, 7);
	destination.setPos(newPos);


	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_UP:
					worm.processUserInput(KEY_UP);
					break;
				case SDLK_DOWN:
					worm.processUserInput(KEY_DOWN);
					break;
				case SDLK_LEFT:
					worm.processUserInput(KEY_LEFT);
					break;
				case SDLK_RIGHT:
					worm.processUserInput(KEY_RIGHT);
					break;
				default:
					break;
				}
			}
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
		
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (mouseX >= 130 && mouseX <= 180 && mouseY >= 20 && mouseY <= 70) {
					worm.SetWorm(newPosWorm);
					apple.setApple();
				}
			}
		}
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);

		game_map.DrawMap1(g_screen);
		Map map_data = game_map.getMap();

		worm.drawWorm(g_screen);

		apple.Draw(g_screen);
		destination.Draw(g_screen);
		game_map.DrawMap2(g_screen);
		if (worm.checkToDestination(destination))
		{
			worm.drawCompleteLv(g_screen);
			

		} 
		else
		    worm.nextStep(map_data, apple);
		SDL_RenderPresent(g_screen);
		
		SDL_Delay(50);
	}
	
}
void GameMode::drawChooseLV(SDL_Renderer* screen)
{
	if (!LoadImg("image//chooselv.png", screen))
	{
		cout << "load menu fail";
	}
	SDL_Rect rectchooselv;
	rectchooselv.x = 0;
	rectchooselv.y = 0;
	rectchooselv.w = SCREEN_WIDTH;
	rectchooselv.h = SCREEN_HEIGHT;
	SDL_RenderCopy(screen, p_object, NULL, &rectchooselv);
	SDL_RenderPresent(screen);
}
void GameMode::handleChooseLV(SDL_Event& e, bool& quit)
{
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			quit = true;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			int mouseX, mouseY;

			SDL_GetMouseState(&mouseX, &mouseY);
			cout << mouseX << " " << mouseY << endl;
			if (mouseX >= 335 && mouseX <= 422 && mouseY >= 134 && mouseY <= 210) {
				state = Lv1;
			}

		}


	}

}
void GameMode::drawNextGame(SDL_Renderer* screen)
{

}