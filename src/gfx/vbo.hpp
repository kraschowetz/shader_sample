#ifndef VBO_HPP
#define VBO_HPP

#include "gfx.hpp"

struct VBO {
	GLuint handle;
	GLint type;
};

struct VBO create_vbo(GLint type);
void destroy_vbo(struct VBO *self);
void bind_vbo(struct VBO *self);
void buffer_vbo(struct VBO *self, void* data, size_t offset, size_t count);

#endif
