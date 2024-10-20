#include "shader.hpp"
#include "gfx.hpp"

using namespace std;

string _load(string src) {
	ifstream file(src);
	string line, code;

	if(!file.is_open()) {
		cerr << "erro ao carregar shader '" 
			  << src 
			  << "\n"
		;
		return "error";
	}

	while(getline(file, line)) {
		code += line + "\n";
	}
	file.close();

	return code;

}

GLuint _compile(GLuint type, string src) {
	GLuint shader;
	shader = glCreateShader(type);
	const char* char_ptr = src.c_str();
	glShaderSource(shader, 1, &char_ptr, NULL);
	glCompileShader(shader);

	return shader;
}

struct Shader create_shader(string vertex, string fragment) {
	struct Shader self;
	
	GLuint vs = _compile(
		GL_VERTEX_SHADER,
		_load(vertex)
	);
	GLuint fs = _compile(
		GL_FRAGMENT_SHADER,
		_load(fragment)
	);
	
	self.handle = glCreateProgram();
	self.vertex_shader = vs;
	self.fragment_shader = fs;

	glAttachShader(self.handle, vs);
	glAttachShader(self.handle, fs);
	glLinkProgram(self.handle);
	glValidateProgram(self.handle);

	return self;
}

void bind_shader(struct Shader *self) {
	glUseProgram(self->handle);
}

void delete_shader(struct Shader *self) {
	glDeleteProgram(self->handle);
	glDeleteShader(self->fragment_shader);
	glDeleteShader(self->vertex_shader);
}

void shader_uniform_float(struct Shader *self, string name, f32 val) {
	GLint location = glGetUniformLocation(self->handle, name.c_str());
	glUniform1f(location, val);
}
