#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "gfx.hpp"

class Renderer {
	private:
		SDL_GLContext context;
	public:
		Renderer(SDL_Window *window, bool debug_specs);
		void prepare();
};

#endif
