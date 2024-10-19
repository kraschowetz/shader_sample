#include "vbo.hpp"

struct VBO create_vbo(GLint type) {
	struct VBO self = {.type = type};
	glGenBuffers(1, &self.handle);

	return self;
}

void destroy_vbo(struct VBO *self) {
	glDeleteBuffers(1, &self->handle);
}

void bind_vbo(struct VBO *self) {
	glBindBuffer(self->type, self->handle);
}

void buffer_vbo(struct VBO *self, void* data, size_t offset, size_t count) {
	bind_vbo(self);
	glBufferData(self->type, count - offset, data, GL_STATIC_DRAW);
}
