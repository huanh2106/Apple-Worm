#include "BaseObject.h"
#include<iostream>
using namespace std;
BaseObject::BaseObject()
{
	p_object = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}
BaseObject::~BaseObject()
{
	Free();
}
bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
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
void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
	SDL_Rect renderquad = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_RenderCopy(des, p_object, clip, &renderquad);
	
}
void BaseObject::Free()
{
	if (p_object != NULL)
	{
		SDL_DestroyTexture(p_object);
		p_object = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}
bool BaseObject::loadFromRenderedText(SDL_Renderer* screen,TTF_Font* gFont, string textureText, SDL_Color textColor)
{
	Free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		cout << "Unable to render text surface! SDL_ttf Error" << endl;
	}
	else
	{
		
		p_object = SDL_CreateTextureFromSurface(screen, textSurface);
		if (p_object == NULL)
		{
			cout << "Co loi o ham loadFromRenderedTex " << endl;
		}
		else
		{
			
			rect_.w = textSurface->w;
			rect_.h = textSurface->h;
		}

		
		SDL_FreeSurface(textSurface);
	}

	
	return p_object!= NULL;
}
void BaseObject::RenderText(SDL_Renderer* des)
{
	SDL_Rect rect{ 580, 68, rect_.w, rect_.h };
	SDL_RenderCopy(des, p_object, NULL, &rect);

}