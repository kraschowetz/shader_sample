#version 410 core

layout(location=0) in vec3 vertex_color;

uniform float time = 1;

out vec4 color;

void main() {
	float sin_time = sin(time);

	if(sin_time < 0) {
		sin_time *= -1;
	}

	color = vec4(
		vertex_color.r + ( 0.75 * sin_time),
		vertex_color.g + (0.75 * sin_time),
		vertex_color.b + (0.25 * sin_time),
		1.0f
	);
}
