#pragma once
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "CommonFunc.h"
#include<iostream>
using namespace std;
class BaseObject
{
public:
		BaseObject();
		~BaseObject();
		void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; }
		SDL_Rect GetRect() const { return rect_; }
		SDL_Texture* GetObject() const { return p_object; }
		virtual bool LoadImg(std::string path, SDL_Renderer* screen);
		void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
		void Free();
	
protected:
	SDL_Rect rect_;
	SDL_Texture* p_object;
};

#endif // BASE_OBJECT_H_
// Path: AppleWorm/BaseObject.cpp