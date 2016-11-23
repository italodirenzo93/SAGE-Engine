#ifndef __CUBE_OBJECT_H__
#define __CUBE_OBJECT_H__

#include "SceneNode.h"
#include "MeshManager.h"
#include "Renderer.h"

class cCubeObject : public cSceneNode
{
public:
	cCubeObject(iRenderer& renderer);
	~cCubeObject();
	void OnRender() override;

private:
	iRenderer&		m_renderer;
	cMeshInfo		m_meshInfo;
	GLuint			m_textureID;
};

#endif