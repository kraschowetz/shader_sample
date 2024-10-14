#include "shader.hpp"
#include "gfx.hpp"

GLuint _compile(GLuint type, std::string& src) {
	GLuint handle;
	handle = glCreateShader(type);

	const char* char_ptr = src.c_str();
	glShaderSource(handle, 1, & char_ptr, nullptr);
	glCompileShader(handle);

	return handle;
}

Shader::Shader(std::string vs_path, std::string fs_path ) {
	vs_handle = _compile(GL_VERTEX_SHADER, vs_path);
	fs_handle = _compile(GL_VERTEX_SHADER, fs_path);
	handle = glCreateProgram();

	glAttachShader(handle, vs_handle);
	glAttachShader(handle, fs_handle);
}

Shader::~Shader() {
	glDeleteProgram(handle);
	glDeleteShader(vs_handle);
	glDeleteShader(fs_handle);
}

void Shader::bind() {
	glUseProgram(handle);
}

void Shader::uniform_int(std::string name, GLint val) {
	glUniform1i(glGetUniformLocation(handle, name.c_str()), val);
}

