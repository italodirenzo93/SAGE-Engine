#version 330 core

// From Vertex Shader
in vec3 fragmentColor;

// What gets drawn on the screen
out vec3 color;

void main() {
	color = fragmentColor;
}