#include "GLBasicShaderProgram.h"
#include <string>
#include <fstream>

namespace SAGE
{
	cGLBasicShaderProgram::cGLBasicShaderProgram() :
		m_vertShader(new cGLShader(eShaderType::VertexShader)),
		m_fragShader(new cGLShader(eShaderType::FragmentShader)),
		m_vertexArrayID(0)
	{
		m_vertShader->LoadFromFile("../Shaders/BasicVertexShader.glsl");
		m_fragShader->LoadFromFile("../Shaders/BasicFragmentShader.glsl");
		AddShader(m_vertShader);
		AddShader(m_fragShader);
		Link();

		// Get uniforms of matrix locations in GLSL
		m_projectionUniform = glGetUniformLocation(GetID(), "matProjection");
		m_viewUniform = glGetUniformLocation(GetID(), "matView");
		m_worldUniform = glGetUniformLocation(GetID(), "matWorld");
	}

	cGLBasicShaderProgram::~cGLBasicShaderProgram()
	{
	}

	void cGLBasicShaderProgram::SetProjectionMatrix(glm::mat4 const& pm)
	{
		m_matProjection = pm;
		glUniformMatrix4fv(m_projectionUniform, 1, GL_FALSE, &m_matProjection[0][0]);
	}

	void cGLBasicShaderProgram::SetViewMatrix(glm::mat4 const& vm)
	{
		m_matView = vm;
		glUniformMatrix4fv(m_viewUniform, 1, GL_FALSE, &m_matView[0][0]);
	}
	void cGLBasicShaderProgram::SetWorldMatrix(glm::mat4 const& wm)
	{
		m_matWorld = wm;
		glUniformMatrix4fv(m_worldUniform, 1, GL_FALSE, &m_matWorld[0][0]);
	}

	void cGLBasicShaderProgram::SetVertexBuffer(GLuint buffer, GLsizei size)
	{
		glEnableVertexAttribArray(m_vertexArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glVertexAttribPointer(m_vertexArrayID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDisableVertexAttribArray(m_vertexArrayID);
	}
}