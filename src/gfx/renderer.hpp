#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "triangle.hpp"
#include "shader.hpp"

class Renderer {
	private:
		SDL_GLContext context;
		struct Shader shader;
		std::vector<Triangle*> triangles;
	public:
		f32 time;	// testando uniforms
		
		Renderer(SDL_Window *window, bool debug_specs);
		~Renderer();
		void prepare();
		void render(SDL_Window *window);
		void spec_vertices();
};

#endif
