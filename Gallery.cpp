#include"Gallery.h"

Gallery::Gallery()
{
	p_object = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;

}
Gallery::~Gallery()
{
	Free();
}
bool Gallery::LoadImg(std::string path, SDL_Renderer* screen)
{
	SDL_Texture* new_texture = NULL;
	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 167, 175, 180));
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture != NULL)
		{
			rect_.w = load_surface->w;
			rect_.h = load_surface->h;
		}
		SDL_FreeSurface(load_surface);
	}
	p_object = new_texture;
	return p_object != NULL;

}
void Gallery::LoadgamePictures()
{
 
}
void Gallery::Free()
{
	if (p_object != NULL)
	{
		SDL_DestroyTexture(p_object);
		p_object = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}
// Path: AppleWorm/AppleWorm.cpp
