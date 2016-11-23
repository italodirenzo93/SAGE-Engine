#version 330 core

// From Vertex Shader
in vec3 fragmentColor;
in vec2 UV;

// What gets drawn on the screen
out vec3 color;

//uniform sampler2D myTextureSampler;

void main() {
	color = fragmentColor;
	
	//color = texture(myTextureSampler, UV).rgb;
}