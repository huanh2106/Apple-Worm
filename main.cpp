#include "BaseObject.h"
#include "CommonFunc.h"
BaseObject g_background;

bool initData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if(ret<0)
		return false;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("Apple Worm by Huy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == NULL)
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL)
		{
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
			{
				success = false;
			}
		}
	}
	{

	}
}
bool LoadBackground()
{
	bool ret = g_background.LoadImg("image//background.png", g_screen);
	if (ret == false)
		return false;
	return true;
}
void close()
{
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();
}
int main(int argc, char* argv[])
{
	if (initData() == false)
		return -1;
	if (LoadBackground() == false)
		return -1;
	bool is_quit = false;
	while (!is_quit)
	{
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
			}
		}
		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);
		g_background.Render(g_screen, NULL);
		SDL_RenderPresent(g_screen);
	}
	close();
	return 0;
}