#include "Game_mode.h"
#include <iostream>
#include <vector>
#include "Timer.h"
using namespace std;
#define playX 544
#define playY 375
#define playW 160
#define playH 110
BaseObject g_background;
BaseObject g_text;
bool g_soundOn = true;

void GameMode::initData() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0) {
		cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}

	g_window = SDL_CreateWindow("Apple Worm by Huy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == nullptr) {
		cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}

	SDL_Surface* iconSurface = IMG_Load("image//icon.png");
	SDL_SetWindowIcon(g_window, iconSurface);
	SDL_FreeSurface(iconSurface);
	g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	if (g_screen == nullptr) {
		cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	g_screen_surface = SDL_GetWindowSurface(g_window);
	SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		cout<<"Loi load Audio: "<<Mix_GetError()<<endl;
		exit(EXIT_FAILURE);
	}
	if (TTF_Init() == -1)
	{
		cout << " Loi khoi tao text" << endl;
		exit(EXIT_FAILURE);
	}

}

bool LoadBackground() {
	if (!g_background.LoadImg("image//background.png", g_screen)) {
		cout << "Failed to load background image!" << std::endl;
		return false;
	}

	return true;
}
bool LoadText(string text)
{
	gFont = TTF_OpenFont("verdanab.ttf", 24);
	if (gFont == NULL)
	{
		cout << "Co loi roi :)))"<<endl;
		return false;
	}
	else
	{
		SDL_Color textColor = { 255, 255, 255 };
		if (!g_text.loadFromRenderedText(g_screen, gFont , text, textColor))
		{
			cout << " loi o loadText" << endl;
			return false;
		}
	}
	return true;
}

bool LoadMusic() {
	g_music = Mix_LoadMUS("music//music.wav");
	if (g_music == NULL)
	{
		std::cout << "Khong the load nhac"<<endl;
		return false;
	}
	g_wineffect = Mix_LoadWAV("music//win.wav");
	if (g_wineffect == NULL)
	{
		cout << " Khong the load nhac" << endl;
	}
	g_next= Mix_LoadWAV("music//next.wav");
	if (g_next == NULL)
	{
		cout << " Khong the load nhac" << endl;
	}
	return true;

}

void close() {
	g_background.Free();
	g_text.Free();
	TTF_CloseFont(gFont);
	gFont = NULL;
	Mix_FreeChunk(g_worm);
	Mix_FreeMusic(g_music);
	SDL_DestroyRenderer(g_screen);
	SDL_DestroyWindow(g_window);
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
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
	LoadMusic();

	bool quit = false;
	while (!quit)
	{
		if (g_soundOn) {
			if (Mix_PlayingMusic() == 0)
			{
				Mix_PlayMusic(g_music, -1);
			}
			else
			{
				if (Mix_PausedMusic() == 1)
				{
					Mix_ResumeMusic();
				}

			}
		}
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
			handleLv2(e, quit);
		}
		else if (state == Lv3)
		{
			handleLv3(e, quit);
		}
		else if (state == Lv4)
		{
			handleLv4(e, quit);
		}
		else if (state == Lv5)
		{
			handleLv5(e, quit);
		}
		else if (state == Lv6)
		{
			handleLv6(e, quit);
		}
		else if (state == Lv7)
		{
			handleLv7(e, quit);
		}
		else if (state == Lv8)
		{
			handleLv8(e, quit);
		}
		else if (state == Lv9)
		{
			handleLv9(e, quit);
		}
		else if (state == Lv10)
		{
			handleLv10(e, quit);
		}
		else if (state == Lv11)
		{
			handleLv11(e, quit);
		}
		else if (state == Lv12)
		{
			handleLv12(e, quit);
		}
		else if (state == Lv13)
		{
			handleLv13(e, quit);
		}
		else if (state == Lv14)
		{
			handleLv14(e, quit);
		}
		else if (state == Lv15)
		{
			handleLv15(e, quit);
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
	SDL_DestroyTexture(p_object);
	SDL_Rect playRect = {playX , playY, playW, playH };
	if (!LoadImg("menu//play.png", screen))
	{
		cout << "load menu fail";
	}

	SDL_RenderCopy(screen, p_object, NULL, &playRect);
	SDL_DestroyTexture(p_object);
	if (g_effectOn)
	{
		drawIconEffectOn(screen);
	}
	else
	{
		drawIconEffectOff(screen);
	}
	if (g_soundOn)
	{
		drawIconMusicOn(g_screen);
	}
	else
	{
		drawIconMusicOff(g_screen);
	}
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
				if (g_effectOn)
				{
					Mix_PlayChannel(-1, g_next, 0);
				}
			}
			if (mouseX >= 950 && mouseX <= 1000 && mouseY >= 20 && mouseY <= 70) {
				g_effectOn = !g_effectOn;
			}
			if (mouseX >= 880 && mouseX <= 930 && mouseY >= 20 && mouseY <= 70) {
				g_soundOn = !g_soundOn;
				if (g_soundOn) {
					Mix_ResumeMusic();
				}
				else {
					Mix_PauseMusic();
				}
			}


		}



	}

}

//Tao Level

void GameMode::handleLv1(SDL_Event& e, bool& quit)
{
	LoadBackground();
	string lv = "Level 01";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map01.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(8, 7);
	vector<Position> newPosStones{ Position(-10,-10) };
	vector<Position> newPosApples{ Position(-1, -1) };
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	vector<Apple> apples{ Apple() };
	apples[0].setPos(newPosApples[0]);
	vector<Stone> stones{ Stone() };
	stones[0].setPos(newPosStones[0]);
	Destination destination;
	Position newPos(15, 7);
	destination.setPos(newPos);
	GameState nextgame = Lv2;
	Playing(quit, e, worm, newPosWorm, destination, apples, newPosApples, stones, newPosStones, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}
void GameMode::handleLv2(SDL_Event& e, bool& quit)
{
	LoadBackground();
	string lv = "Level 02";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map02.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(9, 7);
	vector<Position> newPosStones{ Position(-10,-10) };
	vector<Position> newPosApples{ Position(6, 5) };
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	vector<Apple> apples{ Apple() };
	apples[0].setPos(newPosApples[0]);
	vector<Stone> stones{ Stone() };
	stones[0].setPos(newPosStones[0]);
	Destination destination;
	Position newPos(13, 4);
	destination.setPos(newPos);
	GameState nextgame = Lv3;
	Playing(quit, e, worm, newPosWorm, destination, apples, newPosApples, stones, newPosStones, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}
void GameMode::handleLv3(SDL_Event& e, bool& quit)
{
	LoadBackground();
	string lv = "Level 03";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map03.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(9, 7);
	vector<Position> newPosStone{ Position(-10, -10) };
	vector<Position> newPosApple{ Position(11, 6) };
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	vector<Apple> apple{ Apple() };
	apple[0].setPos(newPosApple[0]);
	vector<Stone> stone{ Stone() };
	stone[0].setPos(newPosStone[0]);
	Destination destination;
	Position newPos(15, 7);
	destination.setPos(newPos);
	GameState nextgame = Lv4;
	Playing(quit, e, worm, newPosWorm, destination, apple, newPosApple, stone, newPosStone, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}
void GameMode::handleLv4(SDL_Event& e, bool& quit)
{
	LoadBackground();
	string lv = "Level 04";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map04.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(9, 7);
	vector<Position> newPosStones{ Position(-10,-10) };
	vector<Position> newPosApples{ Position(12, 6) };
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	vector<Apple> apples{ Apple() };
	apples[0].setPos(newPosApples[0]);
	vector<Stone> stones{ Stone() };
	stones[0].setPos(newPosStones[0]);
	Destination destination;
	Position newPos(15, 4);
	destination.setPos(newPos);
	GameState nextgame = Lv5;
	Playing(quit, e, worm, newPosWorm, destination, apples, newPosApples, stones, newPosStones, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}
void GameMode::handleLv5(SDL_Event& e, bool& quit)
{
	LoadBackground();
	string lv = "Level 05";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map05.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(9, 5);
	vector<Position> newPosStones{ Position(-10,-10) };
	vector<Position> newPosApples{ Position(10, 8) };
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	vector<Apple> apples{ Apple() };
	apples[0].setPos(newPosApples[0]);
	vector<Stone> stones{ Stone() };
	stones[0].setPos(newPosStones[0]);
	Destination destination;
	Position newPos(14, 7);
	destination.setPos(newPos);
	GameState nextgame = Lv6;
	Playing(quit, e, worm, newPosWorm, destination, apples, newPosApples, stones, newPosStones, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}
void GameMode::handleLv6(SDL_Event& e, bool& quit)
{
	LoadBackground();
	string lv = "Level 06";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map06.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(9, 3);
	vector<Position> newPosStones{ Position(-10,-10) };
	vector<Position> newPosApples{ Position(12, 6) };
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	vector<Apple> apples{ Apple() };
	apples[0].setPos(newPosApples[0]);
	vector<Stone> stones{ Stone() };
	stones[0].setPos(newPosStones[0]);
	Destination destination;
	Position newPos(17, 2);
	destination.setPos(newPos);
	GameState nextgame = Lv7;
	Playing(quit, e, worm, newPosWorm, destination, apples, newPosApples, stones, newPosStones, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}
void GameMode::handleLv7(SDL_Event& e, bool& quit)
{
	LoadBackground();
	string lv = "Level 07";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map07.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(9, 3);
	vector<Position> newPosStones{ Position(-10,-10) };
	vector<Position> newPosApples{ Position(12, 7) };
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	vector<Apple> apples{ Apple() };
	apples[0].setPos(newPosApples[0]);
	vector<Stone> stones{ Stone() };
	stones[0].setPos(newPosStones[0]);
	Destination destination;
	Position newPos(16, 4);
	destination.setPos(newPos);
	GameState nextgame = Lv8;
	Playing(quit, e, worm, newPosWorm, destination, apples, newPosApples, stones, newPosStones, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}
void GameMode::handleLv8(SDL_Event& e, bool& quit)
{
	LoadBackground();
	string lv = "Level 08";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map08.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(8, 5);
	vector<Position> newPosStones{ Position(-10,-10) };
	vector<Position> newPosApples{ Position(11, 7) };
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	vector<Apple> apples{ Apple() };
	apples[0].setPos(newPosApples[0]);
	vector<Stone> stones{ Stone() };
	stones[0].setPos(newPosStones[0]);
	Destination destination;
	Position newPos(18, 10);
	destination.setPos(newPos);
	GameState nextgame = Lv9;
	Playing(quit, e, worm, newPosWorm, destination, apples, newPosApples, stones, newPosStones, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}
void GameMode::handleLv9(SDL_Event& e, bool& quit)
{
	LoadBackground();
	string lv = "Level 09";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map09.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(9, 4);
	vector<Position> newPosStones{ Position(-10,-10) };
	vector<Position> newPosApples{ Position(10, 8) };
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	vector<Apple> apples{ Apple() };
	apples[0].setPos(newPosApples[0]);
	vector<Stone> stones{ Stone() };
	stones[0].setPos(newPosStones[0]);
	Destination destination;
	Position newPos(14, 4);
	destination.setPos(newPos);
	GameState nextgame = Lv10;
	Playing(quit, e, worm, newPosWorm, destination, apples, newPosApples, stones, newPosStones, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}
void GameMode::handleLv10(SDL_Event& e, bool& quit)
{
	LoadBackground();
	string lv = "Level 10";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map10.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(10, 6);
	vector<Position> newPosStones{ Position(10,7) };
	vector<Position> newPosApples{ Position(-1, -1) };
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	vector<Apple> apples{ Apple() };
	apples[0].setPos(newPosApples[0]);
	vector<Stone> stones{ Stone() };
	stones[0].setPos(newPosStones[0]);
	Destination destination;
	Position newPos(13, 3);
	destination.setPos(newPos);
	GameState nextgame = Lv11;
	Playing(quit, e, worm, newPosWorm, destination, apples, newPosApples, stones, newPosStones, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}
void GameMode::handleLv11(SDL_Event& e, bool& quit)
{
	LoadBackground();
	string lv = "Level 11";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map11.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(10, 6);
	vector<Position> newPosStones{ Position(14, 7), Position(-10, -10) };
	vector<Position> newPosApples{ Position(11, 5) };
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	vector<Apple> apples{ Apple() };
	apples[0].setPos(newPosApples[0]);
	vector<Stone> stones{ Stone(), Stone() };
	stones[0].setPos(newPosStones[0]);
	stones[1].setPos(newPosStones[1]);
	Destination destination;
	Position newPos(16, 3);
	destination.setPos(newPos);
	GameState nextgame = Lv12;
	Playing(quit, e, worm, newPosWorm, destination, apples, newPosApples, stones, newPosStones, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}


void GameMode::handleLv12(SDL_Event& e, bool& quit)
{
	LoadBackground();
	string lv = "Level 12";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map12.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(7, 6);
	vector<Position> newPosStones{ Position(11, 5), Position(10, 7) };
	vector<Position> newPosApples{ Position(5, 3)};
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	vector<Apple> apples{ Apple()};
	apples[0].setPos(newPosApples[0]);
	vector<Stone> stones{ Stone(), Stone() };
	stones[0].setPos(newPosStones[0]);
	stones[1].setPos(newPosStones[1]);
	Destination destination;
	Position newPos(18, 2);
	destination.setPos(newPos);
	GameState nextgame = Lv13;
	Playing(quit, e, worm, newPosWorm, destination, apples, newPosApples, stones, newPosStones, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}
void GameMode::handleLv13(SDL_Event& e, bool& quit)
{
	LoadBackground();
	string lv = "Level 13";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map13.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(10, 4);
	vector<Position> newPosStones{ Position(8, 5), Position(13, 3) };
	vector<Position> newPosApples{ Position(12, 4) };
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	vector<Apple> apples{ Apple() };
	apples[0].setPos(newPosApples[0]);
	vector<Stone> stones{ Stone(), Stone() };
	stones[0].setPos(newPosStones[0]);
	stones[1].setPos(newPosStones[1]);
	Destination destination;
	Position newPos(16, 8);
	destination.setPos(newPos);
	GameState nextgame = Lv14;
	Playing(quit, e, worm, newPosWorm, destination, apples, newPosApples, stones, newPosStones, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}
void GameMode::handleLv14(SDL_Event& e, bool& quit)
{
	LoadBackground();
	string lv = "Level 14";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map14.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(10, 7);
	vector<Position> newPosStones{ Position(7, 4), Position(11, 4) };
	vector<Position> newPosApples{ Position(6, 6) };
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	vector<Apple> apples{ Apple() };
	apples[0].setPos(newPosApples[0]);
	vector<Stone> stones{ Stone(), Stone() };
	stones[0].setPos(newPosStones[0]);
	stones[1].setPos(newPosStones[1]);
	Destination destination;
	Position newPos(16, 4);
	destination.setPos(newPos);
	GameState nextgame = Lv15;
	Playing(quit, e, worm, newPosWorm, destination, apples, newPosApples, stones, newPosStones, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}
void GameMode::handleLv15(SDL_Event& e, bool& quit)
{
	LoadBackground();
	string lv = "Level 15";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map15.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(12, 9);
	vector<Position> newPosStones{ Position(10, 7), Position(12, 8) };
	vector<Position> newPosApples{ Position(10, 8), Position(11, 7),Position(10, 10), Position(12 , 10), Position(12,6)};

	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	vector<Apple> apples{ Apple(), Apple(), Apple(), Apple(), Apple()};
	apples[0].setPos(newPosApples[0]);
	apples[1].setPos(newPosApples[1]);
	apples[2].setPos(newPosApples[2]);
	apples[3].setPos(newPosApples[3]);
	apples[4].setPos(newPosApples[4]);



	vector<Stone> stones{ Stone(), Stone() };
	stones[0].setPos(newPosStones[0]);
	stones[1].setPos(newPosStones[1]);
	Destination destination;
	Position newPos(16, 4);
	destination.setPos(newPos);
	GameState nextgame = Lv15;
	Playing(quit, e, worm, newPosWorm, destination, apples, newPosApples, stones, newPosStones, game_map, nextgame);
	Mix_FreeChunk(g_worm);
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
	SDL_DestroyTexture(p_object);
	if (g_effectOn)
	{
		drawIconEffectOn(screen);
	}
	else
	{
		drawIconEffectOff(screen);
	}
	if (g_soundOn)
	{
		drawIconMusicOn(g_screen);
	}
	else
	{
		drawIconMusicOff(g_screen);
	}
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
				if (g_effectOn)
				{
					Mix_PlayChannel(-1, g_next, 0);
				}
			}
			if (mouseX >= 460 && mouseX <= 550 && mouseY >= 134 && mouseY <= 210) {
				state = Lv2;
				if (g_effectOn)
				{
					Mix_PlayChannel(-1, g_next, 0);
				}
			}
			if (mouseX >= 585 && mouseX <= 675 && mouseY >= 134 && mouseY <= 210) {
				state = Lv3;
				if (g_effectOn)
				{
					Mix_PlayChannel(-1, g_next, 0);
				}
			}
			if (mouseX >= 710 && mouseX <= 800 && mouseY >= 134 && mouseY <= 210) {
				state = Lv4;
				if (g_effectOn)
				{
					Mix_PlayChannel(-1, g_next, 0);
				}
			}
			if (mouseX >= 835 && mouseX <= 925 && mouseY >= 134 && mouseY <= 210) {
				state = Lv5;
				if (g_effectOn)
				{
					Mix_PlayChannel(-1, g_next, 0);
				}
			}
			if (mouseX >= 335 && mouseX <= 422 && mouseY >= 260 && mouseY <= 336) {
				state = Lv6;
				if (g_effectOn)
				{
					Mix_PlayChannel(-1, g_next, 0);
				}
			}
			if (mouseX >= 460 && mouseX <= 550 && mouseY >= 260 && mouseY <= 336) {
				state = Lv7;
				if (g_effectOn)
				{
					Mix_PlayChannel(-1, g_next, 0);
				}
			}
			if (mouseX >= 585 && mouseX <= 670 && mouseY >= 260 && mouseY <= 336) {
				state = Lv8;
				if (g_effectOn)
				{
					Mix_PlayChannel(-1, g_next, 0);
				}
			}
			if (mouseX >= 710 && mouseX <= 800 && mouseY >= 260 && mouseY <= 336) {
				state = Lv9;
				if (g_effectOn)
				{
					Mix_PlayChannel(-1, g_next, 0);
				}
			}
			if (mouseX >= 835 && mouseX <= 925 && mouseY >= 260 && mouseY <= 336) {
				state = Lv10;
				if (g_effectOn)
				{
					Mix_PlayChannel(-1, g_next, 0);
				}
			}
			if (mouseX >= 335 && mouseX <= 422 && mouseY >= 386 && mouseY <= 462) {
				state = Lv11;
				if (g_effectOn)
				{
					Mix_PlayChannel(-1, g_next, 0);
				}
			}
			if (mouseX >= 460 && mouseX <= 550 && mouseY >= 386 && mouseY <= 462) {
				state = Lv12;
				if (g_effectOn)
				{
					Mix_PlayChannel(-1, g_next, 0);
				}
			}
			if (mouseX >= 585 && mouseX <= 670 && mouseY >= 386 && mouseY <= 462) {
				state = Lv13;
				if (g_effectOn)
				{
					Mix_PlayChannel(-1, g_next, 0);
				}
			}
			if (mouseX >= 710 && mouseX <= 800 && mouseY >= 386 && mouseY <= 462) {
				state = Lv14;
				if (g_effectOn)
				{
					Mix_PlayChannel(-1, g_next, 0);
				}
			}
			if (mouseX >= 835 && mouseX <= 925 && mouseY >= 386 && mouseY <= 462) {
				state = Lv15;
				if (g_effectOn)
				{
					Mix_PlayChannel(-1, g_next, 0);
				}
			}


			if (mouseX >= 190 && mouseX <= 265 && mouseY >= 247 && mouseY <= 380) {
				state = Menu;
				if (g_effectOn)
				{
					Mix_PlayChannel(-1, g_next, 0);
				}
			}

			if (mouseX >= 950 && mouseX <= 1000 && mouseY >= 20 && mouseY <= 70) {
				g_effectOn = !g_effectOn;
			}
			if (mouseX >= 880 && mouseX <= 930 && mouseY >= 20 && mouseY <= 70) {
				g_soundOn = !g_soundOn;
				if (g_soundOn) {
					Mix_ResumeMusic();
				}
				else {
					Mix_PauseMusic();
				}
			}

		}


	}

}
void GameMode::MenuFinish( GameState lv, SDL_Event &e, bool &quit, bool &q)
{
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			q = true;
			quit = true;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			int mouseX, mouseY;

			SDL_GetMouseState(&mouseX, &mouseY);
			cout << mouseX << " " << mouseY << endl;

			if (mouseX >= 440 && mouseX <= 540 && mouseY >= 295 && mouseY <= 395) {
				state = ChooseLV;
				q = true;
			}
			if (mouseX >= 570 && mouseX <= 670 && mouseY >= 295 && mouseY <= 395) {
				q = true;
				quit = true;
			}

			if (mouseX >= 690 && mouseX <= 790 && mouseY >= 295 && mouseY <= 395) {
				state = lv;
				q = true;

			}
			if (mouseX >= 130 && mouseX <= 180 && mouseY >= 20 && mouseY <= 70)
			{
				q = true;
			}


			if (mouseX >= 950 && mouseX <= 1000 && mouseY >= 20 && mouseY <= 70) {
				g_effectOn = !g_effectOn;
			}
			if (mouseX >= 880 && mouseX <= 930 && mouseY >= 20 && mouseY <= 70) {
				g_soundOn = !g_soundOn;
				if (g_soundOn) {
					Mix_ResumeMusic();
				}
				else {
					Mix_PauseMusic();
				}
			}
		}


	}
}
void GameMode::Playing(bool& quit, SDL_Event& e, Worm& worm, Position& newPosWorm, Destination& destination, vector<Apple>& apples, vector<Position>& NewPosApples, vector<Stone>& stones, vector<Position>& NewPosStones, GameMap& game_map, GameState Nextlv)
{
	Timer fps;

	bool q = false;
	bool wineffectPlayed = false;
	while (!q)
	{
		fps.start();
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
				q = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
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

			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (mouseX >= 130 && mouseX <= 180 && mouseY >= 20 && mouseY <= 70)
				{
					worm.SetWorm(newPosWorm);
					for (size_t i = 0; i < apples.size(); i++)
					apples[i].setPos(NewPosApples[i]);
					for (size_t i = 0; i < stones.size(); i++)
						stones[i].setPos(NewPosStones[i]);
				}
				if (mouseX >= 1020 && mouseX <= 1070 && mouseY >= 20 && mouseY <= 70)
				{
					state = ChooseLV;
					if (g_effectOn)
					{
						Mix_PlayChannel(-1, g_next, 0);
					}
					q = true;
				}
				if (mouseX >= 950 && mouseX <= 1000 && mouseY >= 20 && mouseY <= 70)
				{
					g_effectOn = !g_effectOn;
				}
				if (mouseX >= 880 && mouseX <= 930 && mouseY >= 20 && mouseY <= 70)
				{
					g_soundOn = !g_soundOn;
					if (g_soundOn)
					{
						Mix_ResumeMusic();
					}
					else
					{
						Mix_PauseMusic();
					}
				}
			}
		}

		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);
		g_text.RenderText(g_screen);
		if (g_effectOn)
		{
			drawIconEffectOn(g_screen);
		}
		else
		{
			drawIconEffectOff(g_screen);
		}
		if (g_soundOn)
		{
			drawIconMusicOn(g_screen);
		}
		else
		{
			drawIconMusicOff(g_screen);
		}
		game_map.DrawMap1(g_screen);
		Map map_data = game_map.getMap();


		worm.drawWorm(g_screen, apples);
		for (size_t i = 0; i < apples.size(); i++) {
			apples[i].Draw(g_screen);
		}

		bool logic = false;
		for (size_t i = 0; i < stones.size(); i++)
		{
			 stones[i].Draw(g_screen);
			for (size_t j=0; j < stones.size(); j++)
			{

					if (stones[i].StonecheckToOtherStone(stones[j]))
					{

						logic = true;

					}


		}
		if(!logic)
	    worm.Gravity(map_data, stones[i],apples);
		}
		destination.Draw(g_screen);
		game_map.DrawMap2(g_screen);
		if (worm.checkToDestination(destination))
		{
			if (!wineffectPlayed && g_effectOn)
			{
				Mix_PlayChannel(-1, g_wineffect, 0);
				wineffectPlayed = true;
			}
			worm.drawCompleteLv(g_screen);

			MenuFinish(Nextlv, e, quit, q);
		}
		else
		{
			worm.nextStep(map_data, apples, stones);
		}
		SDL_RenderPresent(g_screen);
		int RealTime = fps.get_ticks();
		int time_one_frame = 1000 / FPS;
		if (RealTime < time_one_frame)
		{
			int delay = time_one_frame - RealTime;
			SDL_Delay(delay);
		}

	}
	g_background.Free();
}

void GameMode::drawIconEffectOn( SDL_Renderer* screen) {
	if (!LoadImg("image//effect.png", screen))
	{
		cout << "load menu fail";
	}
	SDL_Rect rectchooselv;
	rectchooselv.x = 950;
	rectchooselv.y = 20;
	rectchooselv.w = 50;
	rectchooselv.h = 50;
	SDL_RenderCopy(screen, p_object, NULL, &rectchooselv);
	SDL_DestroyTexture(p_object);

}
void GameMode::drawIconEffectOff(SDL_Renderer* screen) {
	if (!LoadImg("image//uneffect.png", screen))
	{
		cout << "load menu fail";
	}
	SDL_Rect rectchooselv;
	rectchooselv.x = 950;
	rectchooselv.y = 20;
	rectchooselv.w = 50;
	rectchooselv.h = 50;
	SDL_RenderCopy(screen, p_object, NULL, &rectchooselv);
	SDL_DestroyTexture(p_object);

}
void GameMode::drawIconMusicOn(SDL_Renderer* screen) {
	if (!LoadImg("image//music.png", screen))
	{
		cout << "load menu fail";
	}
	SDL_Rect rectchooselv;
	rectchooselv.x = 880;
	rectchooselv.y = 20;
	rectchooselv.w = 50;
	rectchooselv.h = 50;
	SDL_RenderCopy(screen, p_object, NULL, &rectchooselv);
	SDL_DestroyTexture(p_object);

}
void GameMode::drawIconMusicOff(SDL_Renderer* screen) {
	if (!LoadImg("image//unmusic.png", screen))
	{
		cout << "load menu fail";
	}
	SDL_Rect rectchooselv;
	rectchooselv.x = 880;
	rectchooselv.y = 20;
	rectchooselv.w = 50;
	rectchooselv.h = 50;
	SDL_RenderCopy(screen, p_object, NULL, &rectchooselv);
	SDL_DestroyTexture(p_object);

}
