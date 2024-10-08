#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <SDL2/SDL.h>
#include "../util/util.hpp"

class Canvas {
	private:
		SDL_Window *window;
		SDL_Renderer *renderer;

	public:
		Canvas(u32 width, u32 height);
		~Canvas();

		void render();
};

#endif
