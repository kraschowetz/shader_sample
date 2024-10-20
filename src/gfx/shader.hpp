#ifndef SHADER_HPP
#define SHADER_HPP

#include "gfx.hpp"

struct Shader {
	GLuint handle;
	GLuint vertex_shader;
	GLuint fragment_shader;
};

struct Shader create_shader(std::string vertex, std::string fragment);
void bind_shader(struct Shader *self);
void delete_shader(struct Shader *self);
void shader_uniform_float(struct Shader *self, std::string name, f32 val);

#endif
