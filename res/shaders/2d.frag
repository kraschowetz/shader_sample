#version 410 core

layout(location=0) in vec3 vertex_color;

uniform float time = 1;

out vec4 color;

void main() {
	color = vec4(
		vertex_color.r + (0.25 * sin(time)),
		vertex_color.g + (0.25 * sin(time)),
		vertex_color.b + (0.25 * sin(time)),
		1.0f
	);
}
