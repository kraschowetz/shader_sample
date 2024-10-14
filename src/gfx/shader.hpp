#ifndef SHADER_HPP
#define SHADER_HPP

#include "gfx.hpp"

class Shader {
	private:
		GLuint handle;
		GLuint vs_handle; 
		GLuint fs_handle;
	public:
		Shader(std::string vs_path, std::string fs_path);
		~Shader();
		void bind();
		void uniform_int(std::string name, GLint val);
};

#endif
