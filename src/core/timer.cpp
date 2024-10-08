#include "timer.hpp"
#include <SDL2/SDL.h>

void Timer::start() {
	start_time = SDL_GetTicks();
}

u32 Timer::get_ticks() {
	return SDL_GetTicks() - start_time;
}
