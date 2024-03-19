#ifndef WORM_H_
#define WORM_H_
#include "CommonFunc.h"
#include "BaseObject.h"

class Worm : public BaseObject
{
	Worm();
	~Worm();
	enum WalkType
	{
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
		WALK_UP = 2,
		WALK_DOWN = 3,
	};
    bool LoadImg(std::string path, SDL_Renderer* screen);
	void show(SDL_Renderer* des);
	void handleInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();

private:

	float x_val_;
	float y_val_;
	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;


	SDL_Rect frame_clip_[8];
	Input input_type_;
	int frame_;
	int status_;


};

#endif

// Path: AppleWorm/Worm.cpp