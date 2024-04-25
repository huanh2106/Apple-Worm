#include "Timer.h"

Timer::Timer()
{
	start_tick = 0;

}
Timer::~Timer()
{

}
void Timer::start()
{
	start_tick = SDL_GetTicks();
}

int Timer::get_ticks()
{
	return SDL_GetTicks() - start_tick;

}