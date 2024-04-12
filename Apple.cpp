#include"Apple.h"
#include"CommonFunc.h"
#include<iostream>
using namespace std;

Apple::Apple() : pos(Position(APPLE_POS_X, APPLE_POS_Y)) {}
Apple::~Apple()
{
}
bool Apple::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret)
	{
		
	}
	return ret;
}
void Apple::Draw(SDL_Renderer* screen)
{   
	SDL_Rect rect;
	rect.x = pos.x * APPLE_SIZE + TILE_SIZE - 6;
	rect.y = pos.y * APPLE_SIZE - 14 ;
	rect.w = APPLE_SIZE;
	rect.h = APPLE_SIZE+5;
	if (!LoadImg("image//Apple.png", screen))
	{
		cout << "Khong the load hinh anh" << endl;
	}

	SDL_RenderCopy(screen, p_object, NULL, &rect);
}
// Path: AppleWorm/BaseObject.cpp