#include "BaseObject.h"
#include "CommonFunc.h"
#include "game_map.h"
#include"Worm.h"
#include "Apple.h"
#include <iostream>
BaseObject g_background;

void initData() {
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

int main(int argc, char* argv[]) {
    initData();
    LoadBackground();

    GameMap game_map;

    game_map.LoadMap("map//map01.dat");
    game_map.LoadTiles(g_screen);
    Worm worm(&game_map);
    Apple apple; 
    Destination destination;
    
    bool is_quit = false;
    while (!is_quit) {
        while (SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {
                is_quit = true;
            }
            else if (g_event.type == SDL_KEYDOWN) {
                switch (g_event.key.keysym.sym) {
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
        }
        SDL_RenderClear(g_screen);
      
        g_background.Render(g_screen, NULL);
       
        game_map.DrawMap1(g_screen);
        Map map_data = game_map.getMap();
        
         worm.drawWorm(g_screen);
         
         apple.Draw(g_screen);
         destination.Draw(g_screen);
         game_map.DrawMap2(g_screen);
         SDL_RenderPresent(g_screen);
         worm.nextStep(map_data, apple);
         SDL_Delay(50);
    }
    close();

    return 0;
}
