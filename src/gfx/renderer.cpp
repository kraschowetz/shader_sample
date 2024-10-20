#include "renderer.hpp"
#include "gfx.hpp"
#include "shader.hpp"
#include "vao.hpp"
#include "vbo.hpp"

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
	
	spec_vertices();
	shader = create_shader(
		"./res/shaders/2d.vert",
		"./res/shaders/2d.frag"
	);

	if(!debug_specs) {
		return;
	}

	std::cout << "vendor: " << glGetString(GL_VENDOR) << "\n";
	std::cout << "renderer: " << glGetString(GL_RENDERER) << "\n";
	std::cout << "version: " << glGetString(GL_VERSION) << "\n";
	std::cout << "lang version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
}

void Renderer::spec_vertices() {
	const std::vector<GLfloat> vertex_position = {
		-0.3f, -0.3f, 0.0f,
		0.3f, -0.3f, 0.0f,
		0.0f, 0.3f, 0.0f
	};
	const std::vector<GLfloat> vertex_color = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	const std::vector<GLfloat> vertex_position1 = {
		-1.0f, -1.0f, 0.0f,
		-0.4f, -1.0f, 0.0f,
		-0.7f, -0.7f, 0.0f
	};
	
	vao = create_vao();
	bind_vao(&vao);
	vbo = create_vbo(GL_ARRAY_BUFFER);
	bind_vbo(&vbo);
	
	buffer_vbo(
		&vbo,
		(void*)vertex_position.data(),
		0,
		vertex_position.size() * sizeof(GLfloat)
	);
	
	attr_vao(
		&vao,
		&vbo,
		0,
		3,
		GL_FLOAT,
		0,
		0
	);

	//color
	
	vbo = create_vbo(GL_ARRAY_BUFFER);
	buffer_vbo(
		&vbo,
		(void*)vertex_color.data(),
		0,
		vertex_color.size() * sizeof(GLfloat)
	);

	attr_vao(
		&vao,
		&vbo,
		1,
		3,
		GL_FLOAT,
		0,
		0
	);
	
	//second tri
	
	vao1 = create_vao();
	bind_vao(&vao1);
	vbo1 = create_vbo(GL_ARRAY_BUFFER);
	
	buffer_vbo(
		&vbo1,
		(void*)vertex_position1.data(),
		0,
		vertex_position1.size() * sizeof(GLfloat)
	);
	
	attr_vao(
		&vao1,
		&vbo1,
		0,
		3,
		GL_FLOAT,
		0,
		0
	);
	
	vbo1 = create_vbo(GL_ARRAY_BUFFER);
	
	buffer_vbo(
		&vbo1,
		(void*)vertex_color.data(),
		0,
		vertex_color.size() * sizeof(GLfloat)
	);
	
	attr_vao(
		&vao1,
		&vbo1,
		1,
		3,
		GL_FLOAT,
		0,
		0
	);


	flush_vao_attr({0, 1});
}

void Renderer::prepare() {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	
	glViewport(0,0, 800, 600);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Renderer::render(SDL_Window *window) {
	prepare();
	
	bind_shader(&shader);
	shader_uniform_float(&shader, "time", time);

	bind_vao(&vao);

	glDrawArrays(
		GL_TRIANGLES,
		0,
		3
	);
	
	shader_uniform_float(&shader, "time", time - 1.5);

	bind_vao(&vao1);
	glDrawArrays(
		GL_TRIANGLES,
		0,
		3
	);

	SDL_GL_SwapWindow(window);
}
