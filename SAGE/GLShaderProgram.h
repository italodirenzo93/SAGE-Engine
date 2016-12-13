#ifndef __GLSHADERPROGRAM_H__
#define __GLSHADERPROGRAM_H__

#include "GLShader.h"

#include <vector>
#include <memory>

/*
	This class is intended to act as a base for creating your own shader programs and not to be
	instantiated directly.
	The idea is to have this class act as an interface into your GLSL program and implement additional
	methods to access GLSL parameters.
	ex. SetProjectionMatrix(), SetVertexBuffer(), etc.
*/

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