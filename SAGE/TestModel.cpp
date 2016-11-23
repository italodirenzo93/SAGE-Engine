#include "TestModel.h"

cTestModel::cTestModel() {
	m_pMeshInfo = cMeshManager::LoadFromFilePLY("../Models/bun_zipper_res3_xyz.ply");
}

void cTestModel::OnRender() {
	glEnableVertexAttribArray(0);	// Vertex Shader (layout = 0)
	glBindBuffer(GL_ARRAY_BUFFER, m_pMeshInfo->m_vertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glDrawArrays(GL_TRIANGLES, 0, m_pMeshInfo->m_numElements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pMeshInfo->m_indexBufferID);
	glDrawElements(GL_TRIANGLES, m_pMeshInfo->m_numElements, GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(0);
}