#include "triangle.hpp"
#include "vao.hpp"
#include "vbo.hpp"

using namespace std;

Triangle::Triangle(vector<GLfloat> vert_pos, vector<GLfloat>vert_color) {
	vao = create_vao();
	bind_vao(&vao);
	vbo = create_vbo(GL_ARRAY_BUFFER);
	bind_vbo(&vbo);

	buffer_vbo(
		&vbo,
		(void*)vert_pos.data(),
		0,
		vert_pos.size() * sizeof(GLfloat)
	);

	attr_vao(
		&vao,
		&vbo,
		0,
		3,
		GL_FLOAT,
		0,
		0
	);

	vbo = create_vbo(GL_ARRAY_BUFFER);
	bind_vbo(&vbo);

	buffer_vbo(
		&vbo,
		(void*)vert_color.data(),
		0,
		vert_color.size() * sizeof(GLfloat)
	);

	attr_vao(
		&vao,
		&vbo,
		1,
		3,
		GL_FLOAT,
		0,
		0
	);

	flush_vao_attr({1, 0});
}

Triangle::~Triangle() {
	destroy_vao(&vao);
	destroy_vbo(&vbo);
}

void Triangle::render() {
	bind_vao(&vao);
	glDrawArrays(
		GL_TRIANGLES,
		0,
		3
	);
}
