#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "gfx.hpp"
#include "renderer.hpp"

class Canvas {
	private:
		SDL_Window *window;
		SDL_GLContext gl_context;

		/* make this better  */
		GLuint gl_vertex_array_object = 0;
		GLuint gl_vertex_buffer_object = 0;
		GLuint gl_vertex_buffer_object1 = 0;
		GLuint gl_time_buffer = 0;
		GLuint gl_index_buffer_object = 0;
		GLuint gl_gfx_pipeline_shader_program = 0;

		Renderer *renderer;

	private:
		void spec_vertices();
		void create_gfx_pipeline();
		GLuint create_shader_program(std::string vs, std::string fs);
		std::string load_shader(std::string& path);
	
	public:
		f32 time;

	public:
		Canvas(u32 width, u32 height);
		~Canvas();

		void render();
};

#endif
