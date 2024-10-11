#include "canvas.hpp"
#include <fstream>

/* const char* v_shader_src =  */
/* 	"#version 410 core\n" */
/* 	"in vec4 pos;\n" */
/* 	"void main() {\n" */
/* 	"	gl_Position = vec4(pos.x, pos.y, pos.z, pos.w);\n" */
/* 	"}\n" */
/* ; */
/*  */
/* const char* f_shader_src =  */
/* 	"#version 410 core\n" */
/* 	"out vec4 color;\n" */
/* 	"void main() {\n" */
/* 	"	color = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n" */
/* 	"}\n" */
/* ; */

using namespace std;

inline GLuint compile_shader(GLuint type, string src) {
	GLuint shader;
	shader = glCreateShader(type);
	
	const char* char_ptr = src.c_str();
	glShaderSource(shader, 1, &char_ptr, nullptr);
	glCompileShader(shader);

	return shader;
}

string Canvas::load_shader(string& path) {
	std::ifstream file(path);
	std::string line;
	std::string shader_code;

	if(!file.is_open()) {
		std::cout<<"cant load "<< path << "\n";
		return "//error loading shader\n";
	}

	while(std::getline(file, line)) {
		shader_code += line + "\n";
	}
	file.close();

	return shader_code;
}

GLuint Canvas::create_shader_program(string vs, string fs) {
	GLuint program = glCreateProgram();
	GLuint v_shader = compile_shader(GL_VERTEX_SHADER, load_shader(vs));
	GLuint f_shader = compile_shader(GL_FRAGMENT_SHADER, load_shader(fs));

	glAttachShader(program, v_shader);
	glAttachShader(program, f_shader);
	glLinkProgram(program);

	glValidateProgram(program);

	return program;
}


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

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


	gl_context = SDL_GL_CreateContext(window);
	if(!gl_context) {
		std::cerr << "falha ao iniciar OpenGL";
		return;
	}

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();

	if( glewError != GLEW_OK ) {
		std::cout << "falha ao inicializar glew";
		return;
	}
	if(SDL_GL_SetSwapInterval( 1 ) < 0) {
		std::cout << "falha ao habilitar vsync";
	}
	spec_vertices();
	create_gfx_pipeline();

	std::cout << "vendor: " << glGetString(GL_VENDOR) << "\n";
	std::cout << "renderer: " << glGetString(GL_RENDERER) << "\n";
	std::cout << "gl version: " << glGetString(GL_VERSION) << "\n";
	std::cout << "shading lang version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
}

Canvas::~Canvas() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Canvas::spec_vertices() {
	const std::vector<GLfloat> vertex_position = {
		-0.8f, -0.8f, 0.0f,
		0.8f, -0.8f, 0.0f,
		0.0f, 0.8f, 0.0f
	};
	glGenVertexArrays(1, &gl_vertex_array_object);
	glBindVertexArray(gl_vertex_array_object);
	glGenBuffers(1, &gl_vertex_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, gl_vertex_buffer_object);

	glBufferData(
		GL_ARRAY_BUFFER,
		vertex_position.size() * sizeof(GLfloat),
		vertex_position.data(),
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

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);

}

void Canvas::create_gfx_pipeline() {
	gl_gfx_pipeline_shader_program = create_shader_program(
		"./res/shaders/2d.vert",
		"./res/shaders/2d.frag"
	);
}

void Canvas::render() {
	/* pre render */
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	
	glViewport(0, 0, 1152, 648);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glUseProgram(gl_gfx_pipeline_shader_program);

	/* render */
	
	glBindVertexArray(gl_vertex_array_object);
	glBindBuffer(GL_ARRAY_BUFFER, gl_vertex_array_object);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	SDL_GL_SwapWindow(window);
}
