#pragma once
#ifndef GAME_MODE_H
#define GAME_MODE_H
#include "BaseObject.h"
#include "game_map.h"
#include"Worm.h"
#include "Apple.h"
#include "Stone.h"
enum GameState {
	Menu = 0,ChooseLV, Lv1, Lv2, Lv3, Lv4, Lv5 , Lv6, Lv7, Lv8, Lv9, Lv10, Lv11, Lv12, Lv13, Lv14, Lv15
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
   void handleLv5(SDL_Event& e, bool& quit);
   void handleLv6(SDL_Event& e, bool& quit);
   void handleLv7(SDL_Event& e, bool& quit);
   void handleLv8(SDL_Event& e, bool& quit);
   void handleLv9(SDL_Event& e, bool& quit);
   void handleLv10(SDL_Event& e, bool& quit);
   void handleLv11(SDL_Event& e, bool& quit);
   void handleLv12(SDL_Event& e, bool& quit);
   void handleLv13(SDL_Event& e, bool& quit);
   void handleLv14(SDL_Event& e, bool& quit);
   void handleLv15(SDL_Event& e, bool& quit);
   void drawChooseLV(SDL_Renderer* screen);
   void handleChooseLV(SDL_Event& e, bool& quit);
   void Playing(bool& quit, SDL_Event& e, Worm& worm, Position& newPosWorm, Destination& destination, vector<Apple>& apples, vector<Position>& NewPosApple, vector<Stone>& stones, vector<Position>& NewPosStones, GameMap& game_map, GameState Nextlv);
   void MenuFinish(GameState lv, SDL_Event &e, bool &quit, bool &q);
   void initData();
   

private: 
	GameState state;

};


#endif // !GAME_MODE_H
