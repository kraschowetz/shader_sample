#include "vao.hpp"
#include "gfx.hpp"

struct VAO create_vao() {
	struct VAO self;
	glGenVertexArrays(1, &self.handle);
	
	return self;
}

void destroy_vao(struct VAO *self) {
	glDeleteVertexArrays(1, &self->handle);
}

void bind_vao(struct VAO *self) {
	glBindVertexArray(self->handle);
}

void attr_vao(
	struct VAO *self, struct VBO *vbo, GLint index, GLint size,
	GLenum type, GLsizei stride, size_t offset) {
	
	bind_vao(self);
	bind_vbo(vbo);

	glEnableVertexAttribArray(index);

	switch(type) {
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
}

void disable_vao_attr(struct VAO *self, std::vector<GLint> ids) {
	bind_vao(self);
	for(GLint id : ids) {
		glDisableVertexAttribArray(id);
	}
}

void flush_vao_attr(std::vector<GLint> ids) {
	glBindVertexArray(0);
	for(GLint id : ids) {
		glDisableVertexAttribArray(id);
	}
}
