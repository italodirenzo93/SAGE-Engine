#ifndef __GLBASICSHADERPROGRAM_H__
#define __GLBASICSHADERPROGRAM_H__

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "GLShaderProgram.h"

#include <memory>

namespace SAGE
{
	class cGLBasicShaderProgram : public cGLShaderProgram
	{
	public:
		cGLBasicShaderProgram();
		~cGLBasicShaderProgram();

		glm::mat4 GetProjectionMatrix() const { return m_matProjection; }
		glm::mat4 GetViewMatrix() const { return m_matView; }
		glm::mat4 GetWorldMatrix() const { return m_matWorld; }

		void SetProjectionMatrix(glm::mat4 const& pm);
		void SetViewMatrix(glm::mat4 const& vm);
		void SetWorldMatrix(glm::mat4 const& wm);

		void SetVertexBuffer(GLuint buffer, GLsizei size);

	private:
		std::shared_ptr<cGLShader>	m_vertShader;
		std::shared_ptr<cGLShader>	m_fragShader;

		// Attribute locations
		GLuint const	m_vertexArrayID;

		// Matrices
		glm::mat4		m_matProjection;
		glm::mat4		m_matView;
		glm::mat4		m_matWorld;

		GLuint			m_projectionUniform;
		GLuint			m_viewUniform;
		GLuint			m_worldUniform;
	};
}

#endif // __GLBASICSHADERPROGRAM_H__