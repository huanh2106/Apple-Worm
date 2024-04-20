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
SDL_Texture* Gallery::LoadTexture(std::string path, SDL_Renderer* screen)
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
	return p_object;
	
}
void Gallery::LoadgamePictures()
{  
	pictures.push_back(LoadTexture("img//head.png",g_screen ));
	pictures.push_back(LoadTexture("img//body_horizontal.png", g_screen));
    pictures.push_back(LoadTexture("img//body_vertical.png", g_screen));
	pictures.push_back(LoadTexture("img//tail.png", g_screen));
	pictures.push_back(LoadTexture("img//apple.png", g_screen));
	pictures.push_back(LoadTexture("img//stone.png", g_screen));

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
