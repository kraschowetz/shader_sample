#version 410 core

in vec4 pos;

void main() {
	gl_Position = vec4(pos.x, pos.y, pos.z, pos.w);
}

