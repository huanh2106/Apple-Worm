#pragma once
#ifndef GAME_MODE_H
#define GAME_MODE_H
#include "BaseObject.h"
#include "game_map.h"
#include"Worm.h"
#include "Apple.h"
#include "Stone.h"
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
   void drawIconEffectOn(SDL_Renderer* screen);
   void drawIconEffectOff(SDL_Renderer* screen);
   void drawIconMusicOn(SDL_Renderer* screen);
   void drawIconMusicOff(SDL_Renderer* screen);
   void handleMenu(SDL_Event& e, bool &quit);
   void handleLv1(SDL_Event& e, bool &quit);
   void handleLv2(SDL_Event& e, bool &quit);
   void handleLv3(SDL_Event& e, bool& quit);
   void handleLv4(SDL_Event& e, bool& quit);
   void handleLv9(SDL_Event& e, bool& quit);

   void drawChooseLV(SDL_Renderer* screen);
   void handleChooseLV(SDL_Event& e, bool& quit);
   void Playing(bool& quit, SDL_Event& e, Worm& worm, Position& newPosWorm, Destination& destination, Apple& apple,Position &NewPosApple, Stone& stone, GameMap& game_map, GameState Nextlv);
   void MenuFinish(GameState lv, SDL_Event &e, bool &quit, bool &q);
   void initData();
   

private: 
	GameState state;

};


#endif // !GAME_MODE_H
