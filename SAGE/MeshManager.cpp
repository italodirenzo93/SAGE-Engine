#include "MeshManager.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>

std::shared_ptr<cMeshInfo> cMeshManager::LoadFromFilePLY(std::string const& filename)
{
	std::ifstream ifs(filename);
	if (!ifs.is_open()) {
		std::cerr << "Could not open file: " << filename << std::endl;
		return nullptr;
	}

	std::shared_ptr<cMeshInfo> pMesh = std::make_shared<cMeshInfo>();
	std::string temp;

	// get the number of vertices
	while (ifs >> temp) {
		if (temp == "vertex") {
			ifs >> temp;
			pMesh->m_numVertices = std::stoi(temp);
			break;
		}
	}

	// get the number of elements
	while (ifs >> temp) {
		if (temp == "face") {
			ifs >> temp;
			pMesh->m_numElements = std::stoi(temp);
			break;
		}
	}

	while (ifs >> temp) {
		if (temp == "end_header")
			break;
	}

	// Get the vertices
	std::vector<glm::vec3> vertexData;
	GLuint idx;
	for (idx = 0; idx < pMesh->m_numVertices; ++idx) {
		ifs >> temp;
		GLfloat x = std::stof(temp);

		ifs >> temp;
		GLfloat y = std::stof(temp);

		ifs >> temp;
		GLfloat z = std::stof(temp);

		glm::vec3 vert;
		vert.x = x;
		vert.y = y;
		vert.z = z;
		vertexData.push_back(vert);
	}

	std::vector<GLuint> indexData;
	for (idx = 0; idx < pMesh->m_numElements; ++idx) {
		ifs >> temp;	// throw out the first value

		ifs >> temp;
		GLuint v1 = std::stoi(temp);

		ifs >> temp;
		GLuint v2 = std::stoi(temp);

		ifs >> temp;
		GLuint v3 = std::stoi(temp);

		indexData.push_back(v1);
		indexData.push_back(v2);
		indexData.push_back(v3);
	}

	ifs.close();

	// Create and bind the VAO to the VBO
	glGenVertexArrays(1, &pMesh->m_vertexArrayID);
	glBindVertexArray(pMesh->m_vertexArrayID);

	glGenBuffers(1, &pMesh->m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, pMesh->m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(glm::vec3), vertexData.data(), GL_STATIC_DRAW);

	// Index stuff
	glGenBuffers(1, &pMesh->m_indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pMesh->m_indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLuint), indexData.data(), GL_STATIC_DRAW);

	return pMesh;
}