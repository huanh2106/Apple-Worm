#pragma once
#ifndef APPLE_H
#define APPLE_H
#include "CommonFunc.h"
#include "BaseObject.h"
#define APPLE_POS_X 10
#define APPLE_POS_Y 8
#define APPLE_SIZE 52
class Apple : public BaseObject
{

	public:
	Apple();
	~Apple();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void setPos(Position p) { pos = p; }
	Position getPos() const { return pos; }
	void  removeApple() { pos = Position(-1, -1); }
	void setApple() { pos = Position(APPLE_POS_X, APPLE_POS_Y); }
	void Draw(SDL_Renderer* screen);
	private:
		Position pos;

};



#endif