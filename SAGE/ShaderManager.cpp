#include "ShaderManager.h"
#include <fstream>

cShaderManager::cShaderManager() {}

cShaderManager::~cShaderManager()
{
	for (auto& shader : m_shaders) {
		glDeleteShader(shader.second);
	}
}

GLuint cShaderManager::LoadShader(GLenum type, const char* key, const char* filename)
{
	GLuint shaderID = glCreateShader(type);

	// Read shader source from file
	std::string shaderSource;
	std::ifstream ifs(filename);
	if (ifs.is_open())
	{
		std::string line;
		while (std::getline(ifs, line)) {
			shaderSource += line + "\n";
		}
		ifs.close();
	}

	// Compile shader
	const char * sourcePtr = shaderSource.c_str();
	glShaderSource(shaderID, 1, &sourcePtr, NULL);
	glCompileShader(shaderID);

	// Store the shader in the collection
	m_shaders.insert(std::pair<std::string, GLuint>(key, shaderID));

	return shaderID;
}

GLuint cShaderManager::CreateProgram(const char* vertKey, const char* fragKey)
{
	GLuint vertID = m_shaders.at(vertKey);
	GLuint fragID = m_shaders.at(fragKey);

	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertID);
	glAttachShader(programID, fragID);
	glLinkProgram(programID);
	glDetachShader(programID, vertID);
	glDetachShader(programID, fragID);
	return programID;
}