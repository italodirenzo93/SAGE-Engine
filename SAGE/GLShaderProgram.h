#ifndef __GLSHADERPROGRAM_H__
#define __GLSHADERPROGRAM_H__

#include "GLShader.h"

#include <vector>
#include <memory>

namespace SAGE
{
	class cGLShaderProgram
	{
	protected:
		cGLShaderProgram();
	public:
		virtual ~cGLShaderProgram();

		GLuint GetID() const { return m_programID; }

		void Apply() const;
	protected:
		void AddShader(std::shared_ptr<cGLShader> shader) { m_shaders.push_back(shader); }
		void Link();
	private:
		std::vector<std::shared_ptr<cGLShader>>		m_shaders;
		GLuint						m_programID;
	};
}

#endif