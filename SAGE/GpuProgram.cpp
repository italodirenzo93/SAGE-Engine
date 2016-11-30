#include "GpuProgram.h"
#include <string>
#include <fstream>

cGpuProgram::cGpuProgram(cGLRenderer& renderer) : 
	m_renderer(renderer),
	m_vertexArrayID(0)
{
	std::string line = "";

	// Parse vertex shader source
	std::string vertSrc = "";
	std::ifstream ifs("../Shaders/BasicVertexShader.glsl");
	if (ifs.is_open())
	{
		while (std::getline(ifs, line))
			vertSrc += line + "\n";
	}

	// Compile vertex shader
	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	const char* vertSrcPtr = vertSrc.c_str();
	glShaderSource(m_vertexShaderID, 1, &vertSrcPtr, NULL);
	glCompileShader(m_vertexShaderID);

	// Parse fragment shader source
	std::string fragSrc = "";
	ifs.open("../Shaders/BasicFragmentShader.glsl");
	if (ifs.is_open())
	{
		while (std::getline(ifs, line))
			fragSrc += line + "\n";
	}

	// Compile fragment shader
	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragSrcPtr = fragSrc.c_str();
	glShaderSource(m_fragmentShaderID, 1, &fragSrcPtr, 0);
	glCompileShader(m_fragmentShaderID);

	// Link program
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);
	glLinkProgram(m_programID);
	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);

	// Get handles to matrix inputs
	m_projectionUniform = glGetUniformLocation(m_programID, "matProjection");
	m_viewUniform = glGetUniformLocation(m_programID, "matView");
	m_worldUniform = glGetUniformLocation(m_programID, "matWorld");
}

cGpuProgram::~cGpuProgram()
{
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
}

void cGpuProgram::SetProjectionMatrix(glm::mat4 const& pm)
{
	m_matProjection = pm;
	glUniformMatrix4fv(m_projectionUniform, 1, GL_FALSE, &m_matProjection[0][0]);
}

void cGpuProgram::SetViewMatrix(glm::mat4 const& vm)
{
	m_matView = vm;
	glUniformMatrix4fv(m_viewUniform, 1, GL_FALSE, &m_matView[0][0]);
}
void cGpuProgram::SetWorldMatrix(glm::mat4 const& wm)
{
	m_matWorld = wm;
	glUniformMatrix4fv(m_worldUniform, 1, GL_FALSE, &m_matWorld[0][0]);
}

void cGpuProgram::SetVertexBuffer(GLuint buffer, GLsizei size)
{
	glEnableVertexAttribArray(m_vertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(m_vertexArrayID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDisableVertexAttribArray(m_vertexArrayID);
}

void cGpuProgram::Apply()
{
	glUseProgram(m_programID);
}
