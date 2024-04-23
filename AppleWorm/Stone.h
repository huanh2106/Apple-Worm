#pragma once
#ifndef STONE_H
#define STONE_H
#include "BaseObject.h"

 
#define STONE_POS_X 10
#define STONE_POS_Y 0
#define STONE_SIZE 52

class Stone : public BaseObject
{
public: 
	Stone();
	~Stone();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void setPos(Position p) { pos = p; }
	
	bool StoneCheckToLeftAndRight(Map& map_data, Stone &otherStone);
	Position getPos() const{ return pos; }
	void Draw(SDL_Renderer* screen);
	Position DirLeft() { pos.x -= 1; return pos; }
	Position DirRight() { pos.x += 1; return pos; }
	Position Gravity() { pos.y++; return pos; }
	bool StonecheckToOtherStone( Stone &otherStone);
private:
	Position pos;
	bool operator==(Stone &other)
	{
		return pos.x == other.pos.x && pos.y == other.pos.y;
	}
};





#endif 