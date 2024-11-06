#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "gfx.hpp"
#include "vao.hpp"

class Triangle {
	private:
		struct VAO vao;
		struct VBO vbo;

	public:
		Triangle(
			std::vector<GLfloat> vert_pos,
			std::vector<GLfloat> vert_color
		);
		Triangle(
			std::vector<GLfloat> position,
			GLfloat size,
			std::vector<GLfloat> color
		);	
		~Triangle();
		void render();
};

#endif
