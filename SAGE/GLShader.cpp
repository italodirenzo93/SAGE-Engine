#include "GLShader.h"
#include <SDL.h>
#include <fstream>
#include <sstream>

namespace SAGE
{
	cGLShader::cGLShader(eShaderType type) : m_shaderType(type)
	{
	}

	cGLShader::cGLShader(eShaderType type, std::string const& filename) : m_shaderType(type)
	{
		LoadFromFile(filename);
	}

	cGLShader::~cGLShader()
	{
		glDeleteShader(m_shaderID);
	}

	void cGLShader::LoadFromFile(std::string const& filename)
	{
		std::string line = "";

		// Parse shader source
		std::string src = "";
		std::ifstream ifs(filename);
		if (!ifs.is_open())
		{
			std::ostringstream oss;
			oss << "Could not open file: " << filename;
			throw std::exception(oss.str().c_str());
		}

		// Read source from file
		while (std::getline(ifs, line))
			src += line + "\n";

		LoadFromSource(src);
	}

	void cGLShader::LoadFromSource(std::string const& source)
	{
		// Compile vertex shader
		auto shaderType = (m_shaderType == eShaderType::VertexShader) ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;

		GLuint shaderID = glCreateShader(shaderType);
		const char* vertSrcPtr = source.c_str();
		glShaderSource(shaderID, 1, &vertSrcPtr, NULL);
		glCompileShader(shaderID);

		// Check compile status
		GLint result = GL_FALSE;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			throw std::exception("Unable to compile shader.");
		}

		m_shaderID = shaderID;
	}
}