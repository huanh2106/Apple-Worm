#pragma once
#ifndef GALLERY_H
#define GALLERY_H
#include "CommonFunc.h"
#include "BaseObject.h"
#include <vector>
enum PictureID {
	PIC_WORM_HEAD=0, PIC_WORM_BODY, PIC_WORM_TAIL

};
class Gallery: public BaseObject
{
	std::vector<SDL_Texture*> pictures;

	public:
		Gallery();
		~Gallery();
		bool LoadImg(std::string path, SDL_Renderer* screen);
		void LoadgamePictures();
		SDL_Texture* GetPicture(PictureID id) const { return pictures[id]; }
		void Free();


};
#endif