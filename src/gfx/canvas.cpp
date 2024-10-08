#include "canvas.hpp"
#include <SDL_render.h>
#include <SDL_surface.h>

Canvas::Canvas(u32 width, u32 height) {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "falha ao iniciar SDL";
	}
	window = SDL_CreateWindow(
		"Teste Shaders",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		0
	);

	if(!window) {
		std::cerr << "falha ao inicializar janela";
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED
	);
	if(!renderer) {
		std::cerr << "falha ao inicializar renderizador";
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Canvas::~Canvas() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void Canvas::render() {
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(
		renderer,
		0,
		0,
		0,
		0
	);
	
	SDL_RenderFillRect(renderer, NULL);

	SDL_RenderPresent(renderer);
}
