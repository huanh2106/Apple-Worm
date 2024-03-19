#ifndef MAP_H_
#define MAP_H_
#include "CommonFunc.h"

#include "BaseObject.h"
#include<string>
#define MAX_TILES 40


class Tilemat : public BaseObject

{
	public :
		Tilemat();
	   ~Tilemat()=default;
		
};

class GameMap
{
	public :
		GameMap() {;}
		~GameMap() {;}
		void LoadMap(std::string name);
		void LoadTiles(SDL_Renderer* screen);
		void DrawMap(SDL_Renderer* screen);
        
private:
	Map game_map_;
	Tilemat tile_mat[MAX_TILES];

};
#endif