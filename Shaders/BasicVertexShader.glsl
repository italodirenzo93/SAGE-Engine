#version 330 core

// Inputs
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;

// Matrices
uniform mat4 matProjection;
uniform mat4 matView;
uniform mat4 matWorld;

// Values to be passed to Fragment Shader
out vec3 fragmentColor;

void main() {
	// Combine values into MVP matrix
	gl_Position = (matProjection * matView * matWorld) * vec4(vertexPosition, 1);
	
	// Pass colors to Fragment Shader
	fragmentColor = vertexColor;
}