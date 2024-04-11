#pragma once
#ifndef APPLE_H
#define APPLE_H
#include "CommonFunc.h"
#include "BaseObject.h"

class Apple : public BaseObject
{

	public:
	Apple();
	~Apple();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void setPos(Position p) { pos = p; }
	Position getPos() const { return pos; }
	void  removeApple() { pos = Position(-1, -1); }
	void Draw(SDL_Renderer* screen);
	private:
		Position pos;

};



#endif