#ifndef GFX_HPP
#define GFX_HPP

#include <SDL2/SDL.h>		// IWYU pragma: export
#include <GL/glew.h>		// IWYU pragma: export
#include <SDL_opengl.h>		// IWYU pragma: export
#include <GL/glu.h>		// IWYU pragma: export
#include "../util/util.hpp"	// IWYU pragma: export

static inline void gl_clear_all_errors() {
	while(glGetError() != GL_NO_ERROR) {
	}
}

static inline bool gl_check_err_status(const char* function, int line) {
	while(GLenum err = glGetError()) {
		std::cout 
			<< "GL ERROR "
			<< err
			<< "\tline: "
			<< line
			<< "\tfunction: "
			<< function
			<< "\n";
		return true;
	}
	return false;
}

//evil macro >:)
#define gl_check(x) gl_clear_all_errors(); x; gl_check_err_status(#x, __LINE__);

#endif
