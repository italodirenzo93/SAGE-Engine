#ifndef __GPUPROGRAM_H__
#define __GPUPROGRAM_H__

/*
	Currently implemented in OpenGL. Like a lot of things in this project,
	it will also eventually be abstracted and include a Direct3D backend.
*/

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "GLRenderer.h"

namespace SAGE
{
	class cGpuProgram
	{
	public:
		cGpuProgram(cGLRenderer& renderer);
		~cGpuProgram();

		glm::mat4 GetProjectionMatrix() const { return m_matProjection; }
		glm::mat4 GetViewMatrix() const { return m_matView; }
		glm::mat4 GetWorldMatrix() const { return m_matWorld; }

		void SetProjectionMatrix(glm::mat4 const& pm);
		void SetViewMatrix(glm::mat4 const& vm);
		void SetWorldMatrix(glm::mat4 const& wm);

		void SetVertexBuffer(GLuint buffer, GLsizei size);

		void Apply();

	private:
		cGLRenderer&	m_renderer;

		GLuint			m_vertexShaderID;
		GLuint			m_fragmentShaderID;
		GLuint			m_programID;

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

#endif // __GPUPROGRAM_H__