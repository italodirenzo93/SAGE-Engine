#ifndef __SHADER_MANAGER_H__
#define __SHADER_MANAGER_H__

#include <string>
#include <map>
#include <GL/glew.h>

class cShaderManager
{
public:
	cShaderManager();
	~cShaderManager();
	GLuint LoadShader(GLenum type, const char* key, const char* filename);
	GLuint CreateProgram(const char* vertKey, const char* fragKey);

private:
	std::map<std::string, GLuint>		m_shaders;
};

#endif