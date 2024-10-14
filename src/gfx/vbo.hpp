#ifndef VBO_HPP
#define VBO_HPP

#include "gfx.hpp"

class VBO {
	private:
		GLuint handle;
		GLint type;
		bool dynamic;
	public:
		VBO(GLint type, bool dynamic);
		~VBO();
		void bind();
		void buffer(void* data, size_t offset, size_t count);
};

#endif
