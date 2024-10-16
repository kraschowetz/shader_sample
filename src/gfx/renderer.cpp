#include "renderer.hpp"

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
	create_shader();

	if(!debug_specs) {
		return;
	}

	std::cout << "vendor: " << glGetString(GL_VENDOR) << "\n";
	std::cout << "renderer: " << glGetString(GL_RENDERER) << "\n";
	std::cout << "version: " << glGetString(GL_VERSION) << "\n";
	std::cout << "lang version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
}

std::string _load_shader(std::string src) {
	std::ifstream file(src);
	std::string line;
	std::string code;

	if(!file.is_open()) {
		std::cerr << "error loading shader\n";
		return "error loading shader\n";
	}

	while(std::getline(file, line)) {
		code += line + "\n";
	}
	file.close();

	return code;
}

inline GLuint _compile(GLuint type, std::string src) {
	GLuint shader;
	shader = glCreateShader(type);
	const char* char_ptr = src.c_str();
	glShaderSource(shader, 1, &char_ptr, nullptr);
	glCompileShader(shader);

	return shader;
}

void Renderer::create_shader() {
	shader_program = glCreateProgram();
	GLuint vs = _compile(
		GL_VERTEX_SHADER,
		_load_shader("./res/shaders/2d.vert"));
	GLuint fs = _compile(
		GL_FRAGMENT_SHADER,
		_load_shader("./res/shaders/2d.frag"));

	glAttachShader(shader_program, vs);
	glAttachShader(shader_program, fs);
	glLinkProgram(shader_program);

	glValidateProgram(shader_program);
}

void Renderer::spec_vertices() {
	const std::vector<GLfloat> vertex_position = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};
	const std::vector<GLfloat> vertex_color = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(
		GL_ARRAY_BUFFER,
		vertex_position.size() * sizeof(GLfloat),
		(void*)vertex_position.data(),
		GL_STATIC_DRAW
	);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	//color
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(
		GL_ARRAY_BUFFER,
		vertex_color.size() * sizeof(GLfloat),
		(void*)vertex_color.data(),
		GL_STATIC_DRAW
	);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	//ibo
	const std::vector<GLuint> ibo_data = {
		0, 1, 2
	};

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		ibo_data.size() * sizeof(GLfloat),
		ibo_data.data(),
		GL_STATIC_DRAW
	);
	
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
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
	
	glUseProgram(shader_program);
	GLuint time_uniform = glGetUniformLocation(shader_program, "time");

	glUniform1f(time_uniform, 1.0f);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vao);

	glDrawArrays(
		GL_TRIANGLES,
		0,
		3
	);

	std::cout << vao << "\n";

	SDL_GL_SwapWindow(window);
}
