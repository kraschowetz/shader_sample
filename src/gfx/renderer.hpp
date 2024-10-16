#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "gfx.hpp"

class Renderer {
	private:
		SDL_GLContext context;
		GLuint vbo, ibo, vao, shader_program;
	public:
		f32 time;	// testando uniforms
		
		Renderer(SDL_Window *window, bool debug_specs);
		void prepare();
		void render(SDL_Window *window);
		void spec_vertices();
		void create_shader();
};

#endif
