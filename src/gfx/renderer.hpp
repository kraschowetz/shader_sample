#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "gfx.hpp"
#include "vao.hpp"
#include "shader.hpp"

class Renderer {
	private:
		SDL_GLContext context;
		struct Shader shader;
		struct VBO vbo, vbo1;
		struct VAO vao, vao1;
	public:
		f32 time;	// testando uniforms
		
		Renderer(SDL_Window *window, bool debug_specs);
		void prepare();
		void render(SDL_Window *window);
		void spec_vertices();
};

#endif
