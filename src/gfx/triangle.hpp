#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

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
		~Triangle();
		void render();
};

#endif
