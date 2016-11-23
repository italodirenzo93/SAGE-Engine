#version 330 core

// Inputs
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 vertexUV;

// Model-View-Projection Matrix
uniform mat4 MVP;

// Values to be passed to Fragment Shader
out vec3 fragmentColor;
out vec2 UV;

void main() {
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
	fragmentColor = vertexColor;
	UV = vertexUV;
}