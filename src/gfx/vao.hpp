#ifndef VAO_HPP
#define VAO_HPP

#include "vbo.hpp"

struct VAO {
	GLuint	handle;
};

struct VAO create_vao();
void destroy_vao(struct VAO *self);
void bind_vao(struct VAO *self);
void attr_vao(
	struct VAO *self,
	struct VBO *vbo,
	GLint index,
	GLint size,
	GLenum type,
	GLsizei stride,
	size_t offset
);
void disable_vao_attr(struct VAO *self, std::vector<GLint> ids);
void flush_vao_attr(std::vector<GLint> ids);

#endif
