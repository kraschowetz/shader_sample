#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "gfx.hpp"
#include "renderer.hpp"

class Canvas {
	private:
		SDL_Window *window;
		Renderer *renderer;

	public:
		Canvas(u32 width, u32 height);
		~Canvas();
		
		inline Renderer *get_renderer() { return renderer; }
		void render();
};

#endif
