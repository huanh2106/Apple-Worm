#include "Game_mode.h"
#include <iostream>
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
	//SDL_Surface* iconSurface = IMG_Load("image//icon.png");
	//SDL_SetWindowIcon(g_window, iconSurface);
	//SDL_FreeSurface(iconSurface);
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
		SDL_Color textColor = { 178, 34, 34 };
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
	string lv = "Level 1";
	LoadText(lv);
	GameMap game_map;
    game_map.LoadMap("map//map01.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(8, 7);
	Position newPosApple(-1, -1);
	Position newPosStone(-1, -1);
    Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	Apple apple;
	apple.setPos(newPosApple);
	Destination destination;
	Position newPos(15, 7);
	destination.setPos(newPos);
	Stone stone;
	stone.setPos(newPosStone);
	GameState nextgame = Lv2;
	Playing(quit, e, worm, newPosWorm, destination, apple,newPosApple, stone, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}

void GameMode::handleLv2(SDL_Event& e, bool& quit)
{

	LoadBackground();
	string lv = "Level 2";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map02.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(9, 7);
	Position newPosApple(6, 5);
	Position newPosStone(-1, -1);
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	Apple apple;
	apple.setPos(newPosApple);
	Destination destination;
	Position newPos(13, 4);
	destination.setPos(newPos);
	Stone stone;
	stone.setPos(newPosStone);
	GameState nextgame = Lv3;
	Playing(quit, e, worm, newPosWorm, destination, apple, newPosApple, stone, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}
void GameMode::handleLv3(SDL_Event& e, bool& quit)
{

	LoadBackground();
	string lv = "Level 3";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map03.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(9, 7);
	Position newPosApple(11, 6);
	Position newPosStone(-1, -1);
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	Apple apple;
	apple.setPos(newPosApple);
	Destination destination;
	Position newPos(15, 7);
	destination.setPos(newPos);
	Stone stone;
	stone.setPos(newPosStone);
	GameState nextgame = Lv4;
	Playing(quit, e, worm, newPosWorm, destination, apple,newPosApple, stone, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}
void GameMode::handleLv4(SDL_Event& e, bool& quit)
{

	LoadBackground();
	string lv = "Level 4";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map04.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(9, 7);
	Position newPosApple(12, 6);
	Position newPosStone(-1, -1);
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	Apple apple;
	apple.setPos(newPosApple);
	Destination destination;
	Position newPos(15, 4);
	destination.setPos(newPos);
	Stone stone;
	stone.setPos(newPosStone);
	GameState nextgame = Lv5;
	Playing(quit, e, worm, newPosWorm, destination, apple, newPosApple, stone, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}
void GameMode::handleLv5(SDL_Event& e, bool& quit)
{

	LoadBackground();
	string lv = "Level 5";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map05.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(9, 5);
	Position newPosApple(10, 8);
	Position newPosStone(-1, -1);
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	Apple apple;
	apple.setPos(newPosApple);
	Destination destination;
	Position newPos(14, 7);
	destination.setPos(newPos);
	Stone stone;
	stone.setPos(newPosStone);
	GameState nextgame = Lv6;
	Playing(quit, e, worm, newPosWorm, destination, apple, newPosApple, stone, game_map, nextgame);
	Mix_FreeChunk(g_worm);
}
void GameMode::handleLv9(SDL_Event& e, bool& quit)
{
	LoadBackground();
	string lv = "Level 9";
	LoadText(lv);
	GameMap game_map;
	game_map.LoadMap("map//map09.dat");
	game_map.LoadTiles(g_screen);
	Position newPosWorm(9, 4);
	Position newPosStone(-1, -1);
	Position newPosApple(10, 8);
	Worm worm(&game_map);
	worm.LoadMusic();
	worm.SetWorm(newPosWorm);
	Apple apple;

	Stone stone;
	stone.setPos(newPosStone);
	Destination destination;
	Position newPos(14, 4);
	destination.setPos(newPos);
	GameState nextgame = Lv4;
    Playing(quit, e, worm, newPosWorm, destination, apple,newPosApple, stone, game_map,nextgame);
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
		}


	}
}
void GameMode::Playing(bool &quit, SDL_Event& e, Worm &worm, Position &newPosWorm, Destination &destination,Apple &apple, Position &NewPosApple, Stone &stone, GameMap &game_map, GameState Nextlv)
{
	bool q = false;
	bool wineffectPlayed = false;
	while (!q) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
				q = true;
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
					apple.setPos(NewPosApple);

				}
				if (mouseX >= 1020 && mouseX <= 1070 && mouseY >= 20 && mouseY <= 70) {
					state = ChooseLV;
					if (g_effectOn)
					{
						Mix_PlayChannel(-1, g_next, 0);
					}
					q = true;
				}
				if (mouseX >=950 && mouseX <= 1000 && mouseY >= 20 && mouseY <= 70) {
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

		worm.drawWorm(g_screen, apple);

		apple.Draw(g_screen);
		stone.Draw(g_screen);
		stone.Gravity(map_data);
		destination.Draw(g_screen);
		game_map.DrawMap2(g_screen);
		if (worm.checkToDestination(destination))
		{
			if (!wineffectPlayed&&g_effectOn) {
				Mix_PlayChannel(-1, g_wineffect, 0);
				wineffectPlayed= true;
			}
			worm.drawCompleteLv(g_screen);

			MenuFinish(Nextlv, e, quit, q);

		}
		else
		{
		
			worm.nextStep(map_data, apple, stone);

		}
		SDL_RenderPresent(g_screen);
		SDL_Delay(10);

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