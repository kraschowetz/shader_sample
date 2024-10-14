#include "vao.hpp"

VAO::VAO() {
	glGenVertexArrays(1, &handle);
}

VAO::~VAO() {
	glDeleteVertexArrays(1, &handle);
}

void VAO::bind() {
	glBindVertexArray(handle);
}

void VAO::set_attr(GLuint index, VBO vbo, GLint size, GLenum type, GLsizei stride, size_t offset) {
	this->bind();
	vbo.bind();
	
	//gambiarra maluca pra contornar como o OpenGL trata ints & floats
	switch(type){
		case GL_BYTE:
		case GL_UNSIGNED_BYTE:
		case GL_SHORT:
		case GL_UNSIGNED_SHORT:
		case GL_INT:
		case GL_UNSIGNED_INT:
			glVertexAttribIPointer(
				index,
				size,
				type,
				stride,
				(void*)offset
			);
			break;
		default:
			glVertexAttribPointer(
				index, 
				size,
				type,
				GL_FALSE,
				stride, 
				(void*)offset
			);
			break;
	}
	glEnableVertexAttribArray(index);
}
