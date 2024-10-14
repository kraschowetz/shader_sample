#ifndef VAO_HPP	
#define VAO_HPP

#include "gfx.hpp"
#include "vbo.hpp"

class VAO {
	private:
		GLuint handle;

	public:
		VAO();
		~VAO();
		void bind();
		void set_attr(
			GLuint index, VBO vbo, GLint size, GLenum type,
			GLsizei stride, size_t offset
		);
};

#endif
