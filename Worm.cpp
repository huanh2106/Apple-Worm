#include"Worm.h"
#define WORM_SIZE 40
#define WORM_SPEED 5
#define WORM_FRAME 8
#define WORM_RIGHT 0
#define WORM_LEFT 1
	
#define WORM_UP 2
#define WORM_DOWN 3


Worm::Worm()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WORM_SIZE;
	rect_.h = WORM_SIZE;
	x_val_ = 0;
	y_val_ = 0;
	frame_ = 0;
	status_ = WORM_RIGHT;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.up_ = 0;
	input_type_.down_ = 0;
	p_object = NULL;

}

Worm::~Worm()
{
	Free();
}
bool Worm::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == true)
	{
		width_frame_ = rect_.w / WORM_FRAME;
		height_frame_ = rect_.h;
	}
	return ret;
}
void Worm::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = height_frame_;

		frame_clip_[1].x = width_frame_;
		frame_clip_[1].y = 0;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;

		frame_clip_[2].x = 0;
		frame_clip_[2].y = height_frame_;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;

		frame_clip_[3].x = width_frame_;
		frame_clip_[3].y = height_frame_;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = height_frame_;

		frame_clip_[4].x = 0;
		frame_clip_[4].y = 2 * height_frame_;
		frame_clip_[4].w = width_frame_;
		frame_clip_[4].h = height_frame_;

		frame_clip_[5].x = width_frame_;
		frame_clip_[5].y = 2 * height_frame_;
		frame_clip_[5].w = width_frame_;
		frame_clip_[5].h = height_frame_;

		frame_clip_[6].x = 0;
		frame_clip_[6].y = 3 * height_frame_;
		frame_clip_[6].w = width_frame_;
		frame_clip_[6].h = height_frame_;

		frame_clip_[7].x = width_frame_;
		frame_clip_[7].y = 3 * height_frame_;
		frame_clip_[7].w = width_frame_;
		frame_clip_[7].h = height_frame_;
	}
}
