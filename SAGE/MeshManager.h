#ifndef __MESH_MANAGER_H__
#define __MESH_MANAGER_H__

#include <SDL.h>
#include <GL/glew.h>
#include <string>
#include <memory>

class cMeshInfo
{
public:
	GLuint m_numVertices;
	GLuint m_numElements;
	GLuint m_vertexArrayID;
	GLuint m_vertexBufferID;
	GLuint m_indexBufferID;
	GLuint m_colorBufferID;
	GLuint m_uvBufferID;
};

class cMeshManager
{
public:
	static std::shared_ptr<cMeshInfo> LoadFromFilePLY(std::string const&);
};

#endif