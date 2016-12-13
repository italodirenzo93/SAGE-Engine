#ifndef __GLSHADER_H__
#define __GLSHADER_H__

#include <string>
#include <GL/glew.h>

namespace SAGE
{
	enum eShaderType { VertexShader, FragmentShader };

	enum eShaderStatus { Empty, Source, Compiled, Error };

	class cGLShader
	{
	public:
		// Constructors
		cGLShader(eShaderType type);
		cGLShader(eShaderType type, std::string const& filename);
		~cGLShader();

		// Accessors
		GLuint GetID() const { return m_shaderID; }
		eShaderType GetType() const { return m_shaderType; }

		// Public methods
		void LoadFromFile(std::string const& filename);
		void LoadFromSource(std::string const& source);
	private:
		GLuint		m_shaderID;
		eShaderType	m_shaderType;
	};
}

#endif