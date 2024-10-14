#include "renderer.hpp"
#include "gfx.hpp"
#include <SDL_video.h>

Renderer::Renderer(SDL_Window *window, bool debug_specs = true) {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	context = SDL_GL_CreateContext(window);
	if(!context) {
		std::cerr << "falha ao iniciar opengl\n";
		exit(-1);
	}

	glewExperimental = GL_TRUE;
	GLenum glew_error = glewInit();

	if (glew_error != GLEW_OK) {
		std::cerr << "falha ao iniciar glew\n";
		exit(-1);
	}
	if(SDL_GL_SetSwapInterval(1) < 0) {
		std::cerr << "falha ao habilitar vsync\n";
		exit(-1);
	}

	if(!debug_specs) {
		return;
	}

	std::cout << "vendor: " << glGetString(GL_VENDOR) << "\n";
	std::cout << "renderer: " << glGetString(GL_RENDERER) << "\n";
	std::cout << "version: " << glGetString(GL_VERSION) << "\n";
	std::cout << "lang version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
}

void Renderer::prepare() {
	glClear(GL_DEPTH_BUFFER | GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}
