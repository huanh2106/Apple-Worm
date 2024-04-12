#pragma once
#ifndef GAME_MODE_H
#define GAME_MODE_H
#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include"Worm.h"
#include "Apple.h"

enum GameState {
	Menu = 0,ChooseLV, Lv1, Lv2, Lv3, Lv4, Lv5
};
class GameMode : public BaseObject
{
public:
	GameMode();
   ~GameMode();
   void run(SDL_Event &e);
   bool LoadImg(std::string path, SDL_Renderer* screen);
   void drawMenu(SDL_Renderer* screen);
   void handleMenu(SDL_Event& e, bool &quit);
   void handleLv1(SDL_Event& e, bool &quit);
   
   void drawNextGame(SDL_Renderer* screen);
   void drawChooseLV(SDL_Renderer* screen);
   void handleChooseLV(SDL_Event& e, bool& quit);
   void initData();

private: 
	GameState state;

};


#endif // !GAME_MODE_H
