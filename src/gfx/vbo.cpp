#include "vbo.hpp"

VBO::VBO(GLint type, bool dynamic) {
	this->type = type;
	this->dynamic = dynamic;
	glGenBuffers(1, &handle);
}

VBO::~VBO() {
	glDeleteBuffers(1, &handle);
}

void VBO::bind() {
	glBindBuffer(type, handle);
}

void VBO::buffer(void *data, size_t offset, size_t count) {
	this->bind();
	glBufferData(
		type,
		count - offset,
		data,
		dynamic? GL_DYNAMIC_DRAW : GL_STATIC_DRAW
	);
}
