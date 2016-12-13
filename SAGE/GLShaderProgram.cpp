#include "GLShaderProgram.h"

namespace SAGE
{
	cGLShaderProgram::cGLShaderProgram()
	{

	}

	cGLShaderProgram::~cGLShaderProgram()
	{

	}

	void cGLShaderProgram::Link()
	{
		GLuint program = glCreateProgram();

		// Attach shaders
		for (auto& shader : m_shaders)
			glAttachShader(program, shader->GetID());

		// Link it
		glLinkProgram(program);

		// Check link status
		GLint result = GL_FALSE;
		glGetProgramiv(program, GL_LINK_STATUS, &result);
		if (result == GL_FALSE)
			throw std::exception("Unable to link shader program.");

		// Detach shaders
		for (auto& shader : m_shaders)
			glDetachShader(program, shader->GetID());

		m_programID = program;
	}

	void cGLShaderProgram::Apply() const
	{
		glUseProgram(m_programID);
	}
}