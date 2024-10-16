#include "canvas.hpp"

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
		SDL_WINDOW_OPENGL
	);

	if(!window) {
		std::cerr << "falha ao inicializar janela";
		return;
	}

	renderer = new Renderer(window, true);
}

Canvas::~Canvas() {
	delete renderer;
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Canvas::render() {
	renderer->render(window);
}
