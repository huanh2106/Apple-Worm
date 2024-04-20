#pragma once
#ifndef MAP_H_
#define MAP_H_
#include "BaseObject.h"
#include<string>
#define MAX_TILES 40



class Tilemat : public BaseObject

{
	public :
		Tilemat();
	   ~Tilemat()=default;
		
};

class GameMap : public BaseObject
{
	public :
		GameMap() {;}
		~GameMap() {;}
		void LoadMap(std::string name);
		void LoadTiles(SDL_Renderer* screen);
		void DrawMap1(SDL_Renderer* screen);
		void DrawMap2(SDL_Renderer* screen);
		Map getMap() const{ return game_map_; }
		
        
private:
	Map game_map_;
	Tilemat tile_mat[MAX_TILES];

};
#endif