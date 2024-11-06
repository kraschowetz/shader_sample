#include "triangle.hpp"
#include "gfx.hpp"
#include <cassert>

#define COLOR_CHANNELS 3
#define POSITION_CHANNELS 2

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

Triangle::Triangle(vector<GLfloat> position, GLfloat size, vector<GLfloat> color) {
	assert(position.size() == POSITION_CHANNELS);
	assert(color.size() == COLOR_CHANNELS);
	
	// TODO: avoid vector duplication
	vector<GLfloat> vert_pos = {
		position[0] - size, position[1] - size, 0.0f,
		position[0] + size, position[1] - size, 0.0f,
		position[0], position[1] + size, 0.0f
	};
	vector<GLfloat> vert_color = {
		color[0], color[1], color[2],
		color[0], color[1], color[2],
		color[0], color[1], color[2]
	};

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
