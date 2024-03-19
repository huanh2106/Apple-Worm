#include "BaseObject.h"
#include "CommonFunc.h"
#include "game_map.h"

BaseObject g_background;

void initData() {
    SDL_Init(SDL_INIT_VIDEO);
    g_window = SDL_CreateWindow("Apple Worm by Huy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
    IMG_Init(IMG_INIT_PNG);
}

bool LoadBackground() {
    return g_background.LoadImg("image//background.png", g_screen);
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

    bool is_quit = false;
    while (!is_quit) {
        while (SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {
                is_quit = true;
            }
        }
        SDL_RenderClear(g_screen);
        g_background.Render(g_screen, NULL);
        game_map.DrawMap(g_screen);
        SDL_RenderPresent(g_screen);
    }
    close();
    return 0;
}
