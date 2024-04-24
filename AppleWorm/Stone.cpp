#include "Stone.h"
#include "CommonFunc.h"
#include"BaseObject.h"
#include <iostream>
using namespace std;


Stone::Stone() :pos(Position(STONE_POS_X,STONE_POS_Y)) {}
Stone::~Stone()
{

}
bool Stone::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret)
	{

	}
	return ret;
}
void Stone::Draw(SDL_Renderer* screen)
{
	SDL_Rect rect;
	rect.x = pos.x * STONE_SIZE  + TILE_SIZE - 14;
	rect.y = pos.y * STONE_SIZE - 18;
	rect.w = STONE_SIZE+5;
	rect.h = STONE_SIZE+5;
	if (!LoadImg("image//stone.png", screen))
	{
		cout << "Khong the load hinh anh" << endl;
	}

	SDL_RenderCopy(screen, p_object, NULL, &rect);
	SDL_DestroyTexture(p_object);
}

bool Stone::StoneCheckToLeftAndRight(Map& map_data, Stone &otherStone, Apple &apple)
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	x1 = pos.x * STONE_SIZE / TILE_SIZE;
	x2 = (pos.x * STONE_SIZE + STONE_SIZE + 5) / TILE_SIZE;
	y1 = pos.y * STONE_SIZE / TILE_SIZE;
	y2 = (pos.y * STONE_SIZE + STONE_SIZE - 5) / TILE_SIZE;

	if (map_data.tile[y1][x2] != 0 && map_data.tile[y2][x2] != 0)
	{
		return true;
	}
	else if (map_data.tile[y1][x1] != 0 && map_data.tile[y2][x1] != 0)
	{
		return true;
	}
	
	else if ((pos.y == otherStone.pos.y && pos.x == otherStone.pos.x - 1) || (pos.y == otherStone.pos.y&&pos.x == otherStone.pos.x + 1))
	{   
		cout << "heheh";
		return true;
	}
	else if ((pos.y == apple.getPos().y && pos.x +1 == apple.getPos().x) || (pos.y == apple.getPos().y && pos.x -1 == apple.getPos().x))
	{
		cout << "heheh";
		return true;
	}
	else
	{
		return false;
	}

}
bool Stone::StonecheckToOtherStone(Stone &otherStone) {

	if (pos.x == otherStone.getPos().x && pos.y + 1 == otherStone.getPos().y)
	{
		return true;
	}
	
	return false;
}