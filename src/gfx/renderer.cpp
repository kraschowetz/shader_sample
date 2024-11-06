#include "renderer.hpp"
#define TRIANGLE_LIFETIME 60.0

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
	if(SDL_GL_SetSwapInterval(0) < 0) {
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

Renderer::~Renderer() {
	for(Triangle *tri : triangles) {
		delete tri;
	}
}

void Renderer::spec_vertices() {
	triangles.push_back( 
		new Triangle(
			{
				-0.4f, -0.3f, 0.0f,
				0.2f, -0.3f, 0.0f,
				-0.1f, 0.3f, 0.0f
			},
			{
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
			}
		)
	);
	triangles.push_back( 
		new Triangle(
			{
				-0.3f, -0.3f, 0.0f,
				0.3f, -0.3f, 0.0f,
				0.0f, 0.3f, 0.0f
			},
			{
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
			}
		)
	);
	triangles.push_back( 
		new Triangle(
			{
				-0.2f, -0.3f, 0.0f,
				0.4f, -0.3f, 0.0f,
				0.1f, 0.3f, 0.0f
			},
			{
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
			}
		)
	);

	triangles.push_back(
		new Triangle(
			{0.0f, -0.5f},
			0.5f,
			{0.0f, 1.0f, 0.0f}
		)
	);
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
	
	for(Triangle *tri : triangles) {
		tri->render();
	}

	SDL_GL_SwapWindow(window);

	if(time > TRIANGLE_LIFETIME) {
		for(Triangle *tri : triangles) {
			delete tri;
		}
		triangles.clear();
	}
}
