#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <GL/glu.h>
#include "../util/util.hpp"

class Canvas {
	private:
		SDL_Window *window;
		SDL_GLContext gl_context;

		/* make this better  */
		GLuint gl_vertex_array_object = 0;
		GLuint gl_vertex_buffer_object = 0;
		GLuint gl_gfx_pipeline_shader_program = 0;

	private:
		void spec_vertices();
		void create_gfx_pipeline();

	public:
		Canvas(u32 width, u32 height);
		~Canvas();

		void render();
};

#endif
